#ifndef CREATE_ACTIVATION_FUNCTION_HPP
#define CREATE_ACTIVATION_FUNCTION_HPP

#include <PNEATM/Node/Activation_Function/activation_function_base.hpp>
#include <PNEATM/Node/Activation_Function/activation_function.hpp>
#include <PNEATM/utils.hpp>
#include <memory>

namespace pneatm {

/**
 * @brief A struct for creating activation functions based on input and output types.
 *
 * The `CreateActivationFn` struct provides static template member functions to create activation functions based on
 * the input and output types. It uses variadic templates to handle multiple input and output types.
 */
struct CreateActivationFn {
    /**
     * @brief Create an activation function with specified input and output types.
     * @tparam T1 The first type.
     * @tparam T2 The second type.
     * @tparam Others Variadic template arguments that represent the remaining types.
     * @param iT_in The index of the input type (used for recursive template calls).
     * @param iT_out The index of the output type (used for recursive template calls).
     * @param mono_type Set to true for mono-type activation functions, false for bi-type activation functions. (default is true)
     * @param T2_is_first Set to true if T2 is the input type. (default is false)
     * @return A pointer to the created ActivationFnBase instance.
     */
    template <typename T1, typename T2, typename... Others>
    static ActivationFnBase* get (size_t iT_in, size_t iT_out, bool mono_type = true, bool T2_is_first = false) {
        if (iT_in == 0 && iT_out == 0) {
            if (mono_type) {
                return new ActivationFn <T1, T1> ();
            }
            if (T2_is_first) {
                return new ActivationFn <T2, T1> ();
            } else {
                return new ActivationFn <T1, T2> ();
            }
        }
        size_t new_iT_in = iT_in;
        size_t new_iT_out = iT_out;
        if (new_iT_in > 0) {
            new_iT_in --;
            if (new_iT_out > 0) {
                new_iT_out --;
                // both T_in and T_out are not found
                // Note that if T2 is the last type (aka Others is nothing), the next line will call template <typename T> static CreateNode::NodeBase* get(size_t iT_in, size_t iT_out) which is what we expect as T_in = T_out
                return CreateActivationFn::get<T2, Others...>(new_iT_in, new_iT_out);
            } else {
                // T_out is found and is T1, we keep it
                // It is not a mono type activation function
                return CreateActivationFn::get<T1, T2, Others...>(new_iT_in, new_iT_out, false, true);
            }
        } else {
            new_iT_out --;
            // T_out is not found, because we would return something if both were found
            // However, T_in is found and is T1, we keep it in first place
            // It is not a mono type activation function
            return CreateActivationFn::get<T1, T2, Others...>(new_iT_in, new_iT_out, false, false);
        }
    }

    /**
     * @brief Create an activation function with a single input/output type.
     * @tparam T The input and output type.
     * @param iT_in *Unused*.
     * @param iT_out *Unused*.
     * @return A unique pointer to the created ActivationFnBase instance.
     */
    template <typename T>
    static ActivationFnBase* get (size_t iT_in, size_t iT_out) {
        return new ActivationFn <T, T> ();
        UNUSED (iT_in);
        UNUSED (iT_out);
    }
};

}

#endif	// CREATE_ACTIVATION_FUNCTION_HPP