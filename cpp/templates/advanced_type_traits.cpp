/**
 * @file advanced_type_traits.cpp
 * @brief Examples of C++ type trait metaprogramming techniques
 *
 * This file demonstrates advanced type traits patterns from C++11 and later
 * standards to test the parser's ability to handle complex template
 * metaprogramming constructs.
 */

#include <type_traits>
#include <utility>
#include <tuple>

// Basic type trait examples
template<typename T>
constexpr bool is_pointer_v = std::is_pointer<T>::value;

template<typename T>
constexpr bool is_reference_v = std::is_reference<T>::value;

// Custom type traits
template<typename T, typename = void>
struct has_value_type : std::false_type {};

template<typename T>
struct has_value_type<T, std::void_t<typename T::value_type>> : std::true_type {};

// Type transformations
template<typename T>
using remove_all_extents_t = typename std::remove_all_extents<T>::type;

template<typename T>
using add_const_lvalue_reference_t = typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;

// Detecting callable types
template<typename F, typename... Args>
using invoke_result_t = typename std::invoke_result<F, Args...>::type;

template<typename F, typename... Args>
constexpr bool is_invocable_v = std::is_invocable<F, Args...>::value;

// Type checkers with variable templates (C++14)
template<typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

template<typename Base, typename Derived>
constexpr bool is_base_of_v = std::is_base_of<Base, Derived>::value;

// Advanced detection techniques
namespace detail {
    template<typename Default, typename AlwaysVoid, template<typename...> class Op, typename... Args>
    struct detector {
        using value_t = std::false_type;
        using type = Default;
    };

    template<typename Default, template<typename...> class Op, typename... Args>
    struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
        using value_t = std::true_type;
        using type = Op<Args...>;
    };
}

// Detection idiom
template<template<typename...> class Op, typename... Args>
using is_detected = typename detail::detector<void, void, Op, Args...>::value_t;

template<template<typename...> class Op, typename... Args>
constexpr bool is_detected_v = is_detected<Op, Args...>::value;

template<typename Default, template<typename...> class Op, typename... Args>
using detected_or = detail::detector<Default, void, Op, Args...>;

template<typename Default, template<typename...> class Op, typename... Args>
using detected_or_t = typename detected_or<Default, Op, Args...>::type;

// Detection examples
template<typename T>
using clear_t = decltype(std::declval<T&>().clear());

template<typename T>
using size_t = decltype(std::declval<T&>().size());

template<typename T>
using iterator_t = typename T::iterator;

template<typename T>
constexpr bool has_clear_method_v = is_detected_v<clear_t, T>;

// Type traits for function traits
template<typename T>
struct function_traits;

// Specialization for function pointers
template<typename R, typename... Args>
struct function_traits<R(Args...)> {
    using return_type = R;
    using arguments = std::tuple<Args...>;
    static constexpr size_t arity = sizeof...(Args);
    
    template<size_t N>
    using argument_type = typename std::tuple_element<N, arguments>::type;
};

// Specialization for function pointers
template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> : function_traits<R(Args...)> {};

// Specialization for member function pointers
template<typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...)> : function_traits<R(Args...)> {
    using class_type = C;
};

// Specialization for const member function pointers
template<typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...) const> : function_traits<R(Args...)> {
    using class_type = C;
};

// Specialization for callable objects
template<typename F>
struct function_traits : function_traits<decltype(&F::operator())> {};

// Tag dispatching with type traits
namespace dispatch {
    struct pod_tag {};
    struct non_pod_tag {};
    
    template<typename T>
    T create(pod_tag) {
        // Fast initialization for POD types
        T result;
        return result;
    }
    
    template<typename T>
    T create(non_pod_tag) {
        // Construction for non-POD types
        return T();
    }
    
    template<typename T>
    T create_value() {
        return create<T>(typename std::conditional<
            std::is_pod<T>::value,
            pod_tag,
            non_pod_tag
        >::type{});
    }
}

// Static assertions for compile-time type checking
template<typename T>
void check_type_requirements() {
    static_assert(std::is_default_constructible_v<T>, "T must be default constructible");
    static_assert(std::is_copy_assignable_v<T>, "T must be copy assignable");
    static_assert(std::is_nothrow_move_constructible_v<T>, "T should be nothrow move constructible");
}

// Combining multiple type traits
template<typename T>
struct is_valid_container {
    static constexpr bool value =
        is_detected_v<clear_t, T> &&
        is_detected_v<size_t, T> &&
        is_detected_v<iterator_t, T>;
};

template<typename T>
constexpr bool is_valid_container_v = is_valid_container<T>::value;

// Type categories
template<typename T>
struct type_category {
    static constexpr bool is_reference = std::is_reference_v<T>;
    static constexpr bool is_pointer = std::is_pointer_v<T>;
    static constexpr bool is_arithmetic = std::is_arithmetic_v<T>;
    static constexpr bool is_class = std::is_class_v<T>;
    static constexpr bool is_enum = std::is_enum_v<T>;
};

// C++17 fold expressions with type traits
template<typename... Ts>
constexpr bool all_arithmetic_v = (... && std::is_arithmetic_v<Ts>);

template<typename... Ts>
constexpr bool any_pointer_v = (... || std::is_pointer_v<Ts>);

// Type information at compile time
template<typename T>
constexpr auto type_info() {
    struct info {
        static constexpr bool is_const = std::is_const_v<T>;
        static constexpr bool is_reference = std::is_reference_v<T>;
        static constexpr bool is_pointer = std::is_pointer_v<T>;
        static constexpr bool is_array = std::is_array_v<T>;
        static constexpr bool is_function = std::is_function_v<T>;
        static constexpr bool is_member_pointer = std::is_member_pointer_v<T>;
    };
    return info{};
}

// Advanced conditional compilation based on type properties
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return value * 2.5;
    } else if constexpr (std::is_pointer_v<T>) {
        return *value * 3;
    } else {
        return value.get_value();
    }
}
