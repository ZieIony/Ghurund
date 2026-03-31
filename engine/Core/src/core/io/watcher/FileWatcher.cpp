#include "ghcpch.h"
#include "FileWatcher.h"

namespace Ghurund::Core {
	void FileWatcher::readChangesProc(ULONG_PTR arg) {
		DirectoryWatch* watch = (DirectoryWatch*)arg;
		watch->readChanges();
	}

	FileWatcher::FileWatcher() {
		// TODO: fix thread finishing before it starts
		thread.start();
	}

	FileWatcher::~FileWatcher() {
		watches.clear();
		thread.finish();
	}

	void FileWatcher::addFile(const FilePath& path) {
		WString dir = path.Directory.toString();

		if (!watches.contains(dir)) {
			auto watch = makeShared<DirectoryWatch>(dir);
			watches.put(dir, watch);
			watch->fileChanged += [this](DirectoryWatch&, const FileChange& change)->bool {
				fileChanged(change);
				return true;
			};

			watch->addFile(path);

			thread.post(readChangesProc, (ULONG_PTR)watch.get());
		} else {
			watches.get(dir)->addFile(path);
		}
	}

	void FileWatcher::removeFile(const FilePath& path) {
		WString dir = path.Directory.toString();

		if (!watches.contains(dir))
			return;

		auto watch = watches.get(dir);
		watch->removeFile(path);
		if (watch->FileCount == 0)
			watches.remove(dir);
	}

	void FileWatcher::clearFiles() {
		watches.clear();
	}
}
