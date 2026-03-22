#pragma once

#include "Audio.h"

#include "core/feature/Feature.h"
#include "sound/SoundLoader.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class AudioFeature: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = AudioFeature::GET_TYPE();
#pragma endregion

    private:
        ResourceManager& resourceManager;
        Audio audio;
        IntrusivePointer<SoundLoader> soundLoader;

        void uninitAudioFeature();

    public:
        AudioFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        ~AudioFeature() {
            if (IsInitialized)
                uninitAudioFeature();
        }

        virtual void onInit() override;

        virtual void onUninit() override;

        inline Audio& getAudio() {
            return audio;
        }

        __declspec(property(get = getAudio)) Audio& Audio;
    };
}
