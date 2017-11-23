#include <iostream>
#include <pthread.h>
#include <assert.h>

static pthread_mutex_t mutex;
static pthread_spinlock_t spinlock;
static pthread_rwlock_t  rwlock;

void * thread1_func(void*)
{
	pthread_mutex_lock(&mutex);
}

void * thread2_func(void*)
{
	pthread_spin_lock(&spinlock);
}

void * thread3_func(void*)
{
	pthread_rwlock_rdlock(&rwlock);
}

void * thread4_func(void*)
{
	pthread_rwlock_wrlock(&rwlock);
}

int main(int argc, char** argv)
{
	pthread_mutex_init(&mutex, nullptr);
	pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
	pthread_rwlock_init(&rwlock, nullptr);

	std::cout << "locks were created" << std::endl;

	pthread_mutex_lock(&mutex);
	pthread_spin_lock(&spinlock);
	pthread_rwlock_wrlock(&rwlock);

	std::cout << "locks were locked" << std::endl;

	pthread_t thread1, thread2, thread3, thread4;
	pthread_create(&thread1, nullptr, thread1_func, nullptr);
	pthread_create(&thread2, nullptr, thread2_func, nullptr);
	pthread_create(&thread3, nullptr, thread3_func, nullptr);
	pthread_create(&thread4, nullptr, thread4_func, nullptr);

	std::cout << "threads were created" << std::endl;
	std::cout << "self " << pthread_self() << std::endl;

	pthread_join(thread1, nullptr);
	pthread_join(thread2, nullptr);
	pthread_join(thread3, nullptr);
	pthread_join(thread4, nullptr);

	std::cout << "threads were joined" << std::endl;
	return 0;
}