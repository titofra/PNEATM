#ifndef UTILS_HPP
#define UTILS_HPP

#include <PNEATM/Node/node_base.hpp>
#include <PNEATM/Node/node.hpp>
#include <memory>
#include <cstdlib>

#define UNUSED(expr) do { (void) (expr); } while (0)

namespace pneatm {

struct CreateNode {
    template <typename T1, typename T2, typename... Args>
    static std::unique_ptr<NodeBase> get(size_t iT_in, size_t iT_out, bool mono_type = true, bool T2_is_first = false) {
        if (iT_in == 0 && iT_out == 0) {
            if (mono_type) {
                return std::make_unique<Node <T1, T1>> ();
            }
            if (T2_is_first) {
                return std::make_unique<Node <T2, T1>> ();
            } else {
                return std::make_unique<Node <T1, T2>> ();
            }
        }
        size_t new_iT_in = iT_in;
        size_t new_iT_out = iT_out;
        if (new_iT_in > 0) {
            new_iT_in --;
            if (new_iT_out > 0) {
                new_iT_out --;
                // both T_in and T_out are not found
                // Note that if T2 is the last type (aka Args is nothing), the next line will call template <typename T> static CreateNode::NodeBase* get(size_t iT_in, size_t iT_out) which is what we expect as T_in = T_out
                return CreateNode::get<T2, Args...>(new_iT_in, new_iT_out);
            } else {
                // T_out is found and is T1, we keep it
                // It is not a mono type node
                return CreateNode::get<T1, T2, Args...>(new_iT_in, new_iT_out, false, true);
            }
        } else {
            new_iT_out --;
            // T_out is not found, because we would return something if both were found
            // However, T_in is found and is T1, we keep it in first place
            // It is not a mono type node
            return CreateNode::get<T1, T2, Args...>(new_iT_in, new_iT_out, false, false);
        }
    }

    template <typename T>
    static std::unique_ptr<NodeBase> get(size_t iT_in, size_t iT_out) {
        return std::make_unique<Node <T, T>> ();
        UNUSED (iT_in);
        UNUSED (iT_out);
    }
};

bool Eq_Float (float a, float b, float epsi = 1e-6f) {
    return a < b + epsi && a > b - epsi;
}

float Random_Float (float a, float b, bool a_included = true, bool b_included = true) {
    return (
            ((float) rand () + (float) !a_included)
        ) / (
            (float) (RAND_MAX) + (float) !a_included + (float) !b_included
        ) * (b - a) + a;
}

unsigned int Random_UInt (unsigned int a, unsigned int b) {
    return rand () % (b - a + 1) + a;
}

}

#endif	// UTILS_HPP