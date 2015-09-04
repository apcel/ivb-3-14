#include "hendel.h"

#ifndef __del
	#define __del
	#include <assert.h>

	struct NIL {};
	class IArguments { public: virtual ~IArguments() {} };
	template< class T1 = NIL, class T2 = NIL >
	class Arguments : public IArguments
	{
		public: Arguments() {}
		public: Arguments(T1 i_arg1) :
			arg1(i_arg1) {}
		public: Arguments(T1 i_arg1, T2 i_arg2) :
			arg1(i_arg1), arg2(i_arg2) {}
		public: T1 arg1; T2 arg2;
	};

	class IContainer { public: virtual void Call(IArguments*) = 0; };
	template< class T, class M > class Container : public IContainer {};

	template< class T >
	class Container< T, void (T::*)(void) > : public IContainer
	{
		typedef void (T::*M)(void);

		public: Container(T* c, M m) : m_class(c), m_method(m) {}
		private: T* m_class; M m_method;
		public: void Call(IArguments* i_args)
		{
					(m_class->*m_method)();
		}
	};

	template< class T, class A1 >
	class Container< T, void (T::*)(A1) > : public IContainer
	{
		typedef void (T::*M)(A1);
		typedef Arguments<A1> A;

		public: Container(T* c, M m) : m_class(c), m_method(m) {}
		private: T* m_class; M m_method;
		public: void Call(IArguments* i_args)
		{
					A* a = dynamic_cast< A* >(i_args);
					assert(a);
					if (a) (m_class->*m_method)(a->arg1);
		}
	};


	template< class T, class A1, class A2 >
	class Container< T, void (T::*)(A1, A2) > : public IContainer
	{
		typedef void (T::*M)(A1, A2);
		typedef Arguments<A1, A2> A;

		public: Container(T* c, M m) : m_class(c), m_method(m) {}
		private: T* m_class; M m_method;
		public: void Call(IArguments* i_args)
		{
					A* a = dynamic_cast< A* >(i_args);
					assert(a);
					if (a) (m_class->*m_method)(a->arg1, a->arg2);
		}
	};

	class Delegate
	{
	public:

		Delegate() : m_container(0) {}
		~Delegate() { if (m_container) delete m_container; }

		template< class T, class U > void Connect(T* i_class, U i_method)
		{
			if (m_container) delete m_container;
			m_container = new Container< T, U >(i_class, i_method);
		}

		void operator()()
		{
			m_container->Call(&Arguments<>());
		}

		template< class T1 > void operator()(T1 i_arg1)
		{
			m_container->Call(&Arguments< T1 >(i_arg1));
		}

		template< class T1, class T2 > void operator()(T1 i_arg1, T2 i_arg2)
		{
			m_container->Call(&Arguments< T1, T2 >(i_arg1, i_arg2));
		}

	private:
		IContainer* m_container;
	};
#endif