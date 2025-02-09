#ifndef APPLICATION_H
#define APPLICATION_H
#include <core/include/Subsystem.h>
#include <containers/include/Stl.h>
#include <core/include/Exception.h>
#include <core/include/ThreadPool.h>
#include <util/include/Option.h>
#include <signal.h>
namespace Core
{

	class Application : public ISubsystem,Util::Runnable
	{
		private:
			typedef void(*fn)(int);
			StlMap<int,fn> m_signalRegistry;
			StlMap<string,Util::Option> m_OptionsInfo;
			StlMap<SubsystemId,shared_ptr<ISubsystem>> m_SubsystemInfo;
			StlVector<string> m_CommandOptions;

			int version(string,string);
			void versionS();
			bool processOptions();

			void addOptions();

			int getval();
		public:

			Application();
			virtual ~Application();
			void init();
			void run();
			void shutdown();

			void addOption(Util::Option&);
			void registerSignal(int,fn);
			void onApplicationStart(int argc,char *argv[]);
			bool registerSubsystem(ISubsystem*);
			ISubsystem* getSubsystem(SubsystemId);
	};
}
#endif // APPLICATION_H
