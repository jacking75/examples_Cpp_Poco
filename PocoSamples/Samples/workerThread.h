//출처: https://codezine.jp/article/detail/2626?p=2

#pragma once

#include <Poco/Notification.h>
#include <Poco/NotificationQueue.h>
#include <Poco/ThreadPool.h>
#include <Poco/Thread.h>
#include <Poco/Runnable.h>
#include <Poco/Mutex.h>
#include <Poco/Random.h>

#include <Poco/AutoPtr.h>

#include <iostream>

/*
우선 여러 작업자 스레드(작업 스레드)를 생성gks다.
각 스레드는 공유 자원에 대해 "일"을 취하러 간다.
일이 있으면 그 작업을 수행하고 없으면 새 일을 찾을 때까지 기다린다.
공유 리소스에 작업을 추가하러 간다.
순차적으로 작업자 스레드가 분담해서 처리한다.
일의 추가를 완료하면 모든 일이 처리 될 때까지 기다린다.
*/

// 워커 스레드에 통지 클래스
class WorkNotification : public Poco::Notification
{
	// 통지 번호
	int    _ix;

public:
	WorkNotification(int i) : _ix(i)
	{
	}

	// 가지고 있는 번호를 반환
	int ix() const
	{
		return _ix;
	}

	// 명령어 처리
	void execute()
	{
		// 난수 클래스
		Poco::Random  rnd;

		rnd.seed();

		// 난수로 Sleep 한다（0～199밀리초）
		Poco::Thread::sleep(rnd.next(200));
	}
};

// 워커 스레드 클래스
// 통지 queue에서 통지 오브젝트를 추출하고, 실행한다.
class Worker : public Poco::Runnable
{
	// 스레드 식별명
	std::string         _name;

	// 통지 queue
	Poco::NotificationQueue&  _queue;

	// 배타 처리용 Mutex
	static Poco::FastMutex    _mutex;

public:
	Worker(const std::string& name, Poco::NotificationQueue& queue) :
		_name(name), _queue(queue)
	{
	}

	// 스레드의 메인 처리
	void run()
	{
		for (;;) {
			// 통지 queue에서 데이터를 얻을 때까지 대기
			Poco::AutoPtr<Poco::Notification> pNf(_queue.waitDequeueNotification());
			if (pNf) {
				WorkNotification* pWorkNf = dynamic_cast<WorkNotification*>(pNf.get());
				if (pWorkNf) {
					{
						Poco::FastMutex::ScopedLock lock(_mutex);
						std::cout << _name << " excute No." << pWorkNf->ix() << std::endl;
					}
					// 명령 실행
					pWorkNf->execute();
				}
			}
			else
				break;  // 반환 값이 NULL이면 스레드를 종료
		}
	}
};
Poco::FastMutex Worker::_mutex; // static 변수의 실체

void Sample_WorkerThread()
{
	// 통지 오브젝트 queue
	Poco::NotificationQueue queue;

	// 워커 스레드를 만든다
	Worker worker1("Worker-1", queue);
	Worker worker2("Worker-2", queue);
	Worker worker3("Worker-3", queue);

	// 스레드 풀
	Poco::ThreadPool pool;

	// 각 워커 스레드 등록과 시작
	pool.start(worker1);
	pool.start(worker2);
	pool.start(worker3);

	// 통지 오브젝트 50개를 queue에 넣는다
	for (int i = 0; i < 50; ++i) {
		queue.enqueueNotification(new WorkNotification(i));
	}

	// queue가 빌 때까지 메인스레드는 대기
	while (!queue.empty()) {
		Poco::Thread::sleep(200);
	}

	// 모든 워커 스레드가 처리 대기될 때까지 Sleep 해 둔다
	Poco::Thread::sleep(200);

	// 모든 워커 스레드에 종료를 지시
	queue.wakeUpAll();

	// 모든 워커 스레드의 종료 대기
	pool.joinAll();
}