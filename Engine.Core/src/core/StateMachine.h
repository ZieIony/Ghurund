#pragma once

#include "core/logging/Logger.h"
#include "core/collection/List.h"
#include "core/threading/CriticalSection.h"

#include <functional>

namespace Ghurund {
    template<class T> class StateMachine {
    private:
        template<class T> struct State {
            T state;
            std::function<void()> onStateEnter;
            std::function<void()> onStateLeave;

            State(T state) {
                this->state = state;
            }

            State(T state, std::function<void()> onStateEnter) {
                this->state = state;
                this->onStateEnter = onStateEnter;
            }

            State(T state, std::function<void()> onStateEnter, std::function<void()> onStateLeave) {
                this->state = state;
                this->onStateEnter = onStateEnter;
                this->onStateLeave = onStateLeave;
            }
        };

        template<class T> struct Edge {
            T from;
            T to;
            std::function<void()> onStateChange;

            Edge(T from, T to) {
                this->from = from;
                this->to = to;
            }

            Edge(T from, T to, std::function<void()> onStateChange) {
                this->from = from;
                this->to = to;
                this->onStateChange = onStateChange;
            }
        };

        State<T> currentState;
        List<State<T>*> states;
        List<Edge<T>*> edges;
        mutable CriticalSection cs;

        void findState(T state) {
            for (size_t i = 0; i < states.Size; i++) {
                State<T>* s = states[i];
                if (s->state == state) {
                    currentState = *s;
                    return;
                }
            }
            currentState = State<T>(state);
        }

    public:
        StateMachine(T initialState): currentState(initialState) {}

        ~StateMachine() {
            for (size_t i = 0; i < edges.Size; i++)
                delete edges[i];
            for (size_t i = 0; i < states.Size; i++)
                delete states[i];
        }

        void addState(T state) {
            states.add(ghnew State<T>(state));
        }

        void addState(T state, std::function<void()> onStateEnter) {
            states.add(ghnew State<T>(state, onStateEnter));
        }

        void addState(T state, std::function<void()> onStateEnter, std::function<void()> onStateLeave) {
            states.add(ghnew State<T>(state, onStateEnter, onStateLeave));
        }

        void addEdge(T from, T to) {
            edges.add(ghnew Edge<T>(from, to));
        }

        void addEdge(T from, T to, std::function<void()> onStateChange) {
            edges.add(ghnew Edge<T>(from, to, onStateChange));
        }

        Status setState(T state) {
            cs.enter();

            Status result = Status::OK;

            for (size_t i = 0; i < edges.Size; i++) {
                Edge<T>* e = edges[i];
                if (e->from == currentState.state && e->to == state) {
                    if (currentState.onStateLeave != nullptr)
                        currentState.onStateLeave();
                    findState(e->to);
                    if (e->onStateChange != nullptr)
                        e->onStateChange();
                    if (currentState.onStateEnter != nullptr)
                        currentState.onStateEnter();
                    goto cleanUp;
                }
            }

            result = Status::INV_PARAM;
            Logger::log(LogType::WARNING, result, _T("No edge for specified states: {0} -> {1}\n"), currentState.state, state);

        cleanUp:
            cs.leave();
            return result;
        }

        T getState() const {
            cs.enter();
            T state = currentState.state;
            cs.leave();
            return state;
        }
    };
}