#ifndef CONNECTION_HPP
#define CONNECTION_HPP

namespace vrneat {

class Connection {
	public:
		Connection(const unsigned int innovId, const unsigned int inNodeId, const unsigned int outNodeId, const unsigned int inNodeRecu, float weight, bool enabled);

	private:
		const unsigned int innovId;
		const unsigned int inNodeId;
		const unsigned int outNodeId;
		const unsigned int inNodeRecu;
		float weight;
		bool enabled;

	template <typename... Args>
	friend class Genome;
};

}

#endif	// CONNECTION_HPP