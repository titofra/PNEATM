#ifndef NODE_BASE_HPP
#define NODE_BASE_HPP

#include <functional>
#include <iostream>
#include <cstring>

namespace pneatm {

class NodeBase{
    public:
        virtual ~NodeBase() {};

		virtual void setActivationFn (void* f) = 0;
		virtual void setResetValue (void* value) = 0;

		virtual void loadInput (void* value) = 0;	// for input nodes only
		virtual void AddToInput (void* value, float scalar) = 0;	// TODO: too dirty
		virtual void* getOutput () = 0;

		virtual void process () = 0;
		virtual void reset () = 0;

		virtual void print (std::string prefix = "") = 0;

	protected:
		unsigned int id;
		int layer;
		unsigned int index_T_in;
		unsigned int index_T_out;

	template <typename... Args>
	friend class Genome;
};

}

#endif	// NODE_BASE_HPP