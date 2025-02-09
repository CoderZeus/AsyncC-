#ifndef ASYNCTASK_H
#define ASYNCTASK_H
#include <containers/include/Stl.h>
#include <async/include/TaskInfo.h>
#include <core/include/NotifyManager.h>
#include <core/include/Synchronizer.h>

namespace Async
{
	class ITask
	{
			template<typename Fn>
                        void dispatchTask(Fn&& Task,Core::SyncKey Key)
                        {
                                Core::NotifyManager::getInstance()->dispatch(make_shared<TaskInfo<Fn>>(Task),Key);
                        }

			template<typename Fn,typename Resp>
                        void dispatchTask(Fn&& Task,Resp&& Response,Core::SyncKey Key)
                        {
                        	Core::NotifyManager::getInstance()->dispatch(make_shared<TaskInfoResponse<Fn,Resp>>(Task,Response),Key);
			}
	
			StlQueue<shared_ptr<ITaskInfo> > mTaskQ;	
		public:
			ITask()
			{
			}

			virtual ~ITask()
			{
				
			}

			template<typename Fn>
			ITask(Fn&& Task,Core::SyncKey Key)
			{
				this->dispatchTask(Task,Key);
			}

			template<typename Fn,typename Resp>
			ITask(Fn&& Task,Resp&& Response,Core::SyncKey Key)
			{
				this->dispatchTask(Task,Response,Key);
			}
			
		
			template<typename Fn>
			ITask& add(Fn&& Task)
			{
				this->dispatchTask(Task,this->getKey());
				return *this;
			}

			template<typename Fn,typename Resp>
			ITask& add(Fn&& Task,Resp&& Response)
			{
				this->dispatchTask(Task,Response,this->getKey());	
				return *this;
			}

			virtual Core::SyncKey getKey() = 0;
	};

	class SyncTask	: public ITask
	{
			Core::SyncKey mKey;
		public:

			SyncTask():mKey(Core::Synchronizer::getSyncKey())
                        {
                                
                        } 
			
			template<typename Fn>
                        SyncTask(Fn&& Task) : mKey(Core::Synchronizer::getSyncKey()),ITask(Task,mKey)
			{
			
			}

			template<typename Fn,typename Resp>
                        SyncTask(Fn&& Task,Resp&& Response) : mKey(Core::Synchronizer::getSyncKey()),ITask(Task,Response,mKey)
                        {

                        }

			Core::SyncKey getKey() override
			{
				return this->mKey;
			}
	};

	class AsyncTask  : public ITask
        {
                public:

                        AsyncTask()
                        {

                        }

                        template<typename Fn>
                       	AsyncTask(Fn&& Task) : ITask(Task,Core::Synchronizer::getSyncKey())
                        {

                        }

                        template<typename Fn,typename Resp>
                        AsyncTask(Fn&& Task,Resp&& Response): ITask(Task,Response,Core::Synchronizer::getSyncKey())
                        {

                        }

                        Core::SyncKey getKey() override
                        {
                                return Core::Synchronizer::getSyncKey();;
                        }
        };

}
#endif //ASYNCTASK_H
