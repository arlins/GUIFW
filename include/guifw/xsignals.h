#pragma once
#include "sigslot.h"


namespace xsignals
{
	namespace details
	{
		template <typename F>
		struct simple_function_type;

		template <>
		struct simple_function_type<void()>
		{
			enum { arity = 0};
		};

		template <typename arg1_type>
		struct simple_function_type<void(arg1_type)>
		{
			enum { arity = 1};
			typedef arg1_type arg1_type;
		};

		template <typename arg1_type, typename arg2_type>
		struct simple_function_type<void(arg1_type, arg2_type)>
		{
			enum { arity = 2};
			typedef arg1_type arg1_type;
			typedef arg2_type arg2_type;
		};

		template <typename arg1_type, typename arg2_type, typename arg3_type>
		struct simple_function_type<void(arg1_type, arg2_type, arg3_type)>
		{
			enum { arity = 3};
			typedef arg1_type arg1_type;
			typedef arg2_type arg2_type;
			typedef arg3_type arg3_type;
		};

		template <typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type>
		struct simple_function_type<void(arg1_type, arg2_type, arg3_type, arg4_type)>
		{
			enum { arity = 4};
			typedef arg1_type arg1_type;
			typedef arg2_type arg2_type;
			typedef arg3_type arg3_type;
			typedef arg4_type arg4_type;
		};

		template <typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type, typename arg5_type>
		struct simple_function_type<void(arg1_type, arg2_type, arg3_type, arg4_type, arg5_type)>
		{
			enum { arity = 5};
			typedef arg1_type arg1_type;
			typedef arg2_type arg2_type;
			typedef arg3_type arg3_type;
			typedef arg4_type arg4_type;
			typedef arg5_type arg5_type;
		};

		template <typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type, typename arg5_type, typename arg6_type>
		struct simple_function_type<void(arg1_type, arg2_type, arg3_type, arg4_type, arg5_type, arg6_type)>
		{
			enum { arity = 6};
			typedef arg1_type arg1_type;
			typedef arg2_type arg2_type;
			typedef arg3_type arg3_type;
			typedef arg4_type arg4_type;
			typedef arg5_type arg5_type;
			typedef arg6_type arg6_type;
		};

		template <typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type, typename arg5_type, typename arg6_type, typename arg7_type>
		struct simple_function_type<void(arg1_type, arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, arg7_type)>
		{
			enum { arity = 7};
			typedef arg1_type arg1_type;
			typedef arg2_type arg2_type;
			typedef arg3_type arg3_type;
			typedef arg4_type arg4_type;
			typedef arg5_type arg5_type;
			typedef arg6_type arg6_type;
			typedef arg7_type arg7_type;
		};

		template <typename arg1_type, typename arg2_type, typename arg3_type, typename arg4_type, typename arg5_type, typename arg6_type, typename arg7_type, typename arg8_type>
		struct simple_function_type<void(arg1_type, arg2_type, arg3_type, arg4_type, arg5_type, arg6_type, arg7_type, arg8_type)>
		{
			enum { arity = 8};
			typedef arg1_type arg1_type;
			typedef arg2_type arg2_type;
			typedef arg3_type arg3_type;
			typedef arg4_type arg4_type;
			typedef arg5_type arg5_type;
			typedef arg6_type arg6_type;
			typedef arg7_type arg7_type;
			typedef arg8_type arg8_type;
		};


		template <class F, unsigned N = simple_function_type<F>::arity> class sigslot_signal;

		template <class F> class sigslot_signal<F, 0>
			: public sigslot::signal0<> {};
		template <class F> class sigslot_signal<F, 1>
			: public sigslot::signal1<typename simple_function_type<F>::arg1_type> {};
		template <class F> class sigslot_signal<F, 2>
			: public sigslot::signal2<typename simple_function_type<F>::arg1_type,
																typename simple_function_type<F>::arg2_type> {};
		template <class F> class sigslot_signal<F, 3>
			: public sigslot::signal3<typename simple_function_type<F>::arg1_type,
																typename simple_function_type<F>::arg2_type,
																typename simple_function_type<F>::arg3_type> {};
		template <class F> class sigslot_signal<F, 4>
			: public sigslot::signal4<typename simple_function_type<F>::arg1_type,
																typename simple_function_type<F>::arg2_type,
																typename simple_function_type<F>::arg3_type,
																typename simple_function_type<F>::arg4_type> {};
		template <class F> class sigslot_signal<F, 5>
			: public sigslot::signal5<typename simple_function_type<F>::arg1_type,
																typename simple_function_type<F>::arg2_type,
																typename simple_function_type<F>::arg3_type,
																typename simple_function_type<F>::arg4_type,
																typename simple_function_type<F>::arg5_type> {};
		template <class F> class sigslot_signal<F, 6>
			: public sigslot::signal6<typename simple_function_type<F>::arg1_type,
																typename simple_function_type<F>::arg2_type,
																typename simple_function_type<F>::arg3_type,
																typename simple_function_type<F>::arg4_type,
																typename simple_function_type<F>::arg5_type,
																typename simple_function_type<F>::arg6_type> {};
		template <class F> class sigslot_signal<F, 7>
			: public sigslot::signal7<typename simple_function_type<F>::arg1_type,
																typename simple_function_type<F>::arg2_type,
																typename simple_function_type<F>::arg3_type,
																typename simple_function_type<F>::arg4_type,
																typename simple_function_type<F>::arg5_type,
																typename simple_function_type<F>::arg6_type,
																typename simple_function_type<F>::arg7_type> {};
		template <class F> class sigslot_signal<F, 8>
			: public sigslot::signal8<typename simple_function_type<F>::arg1_type,
																typename simple_function_type<F>::arg2_type,
																typename simple_function_type<F>::arg3_type,
																typename simple_function_type<F>::arg4_type,
																typename simple_function_type<F>::arg5_type,
																typename simple_function_type<F>::arg6_type,
																typename simple_function_type<F>::arg7_type,
																typename simple_function_type<F>::arg8_type> {};
	} //namespace details


	typedef sigslot::has_slots	trackable;


	template <class Signature>
	class signal : public details::sigslot_signal<Signature>
	{
	};


} //namespace xsignals

