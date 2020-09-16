NAT translator from input files.

Installation:

Requires cmake, make, and g++ in (preferably linux) system to run.

In terminal, type in "cmake CMakeLists.txt", then type in "make".

Usage:

To run, requires two input files passed to program as command line arguments:

./natty NAT FLOW

NAT input file: ip1:port1,ip2:port2 where one of ip1 or port1 can be "*" for
any

FLOW input file: ip:port

For each line/ip:port of FLOW, will return the mapping as specified in NAT,
else returns no mapping message. Output will appear in file named OUTPUT.

Implementation Details:

Creates a TrieMap class specific to the NAT mapping problem. Given that all
the ip addresses are numbers seperated by periods, could simply have each
number be the trie edge. The "*" in the NAT input file case is handled by
a specific top-level map<int, string> in the TrieMap class for ip addresses,
along with being INT_MIN as a trie edge if "*" is a port. To specify the
differences between a port number and an ipv4 component, the port numbers are
always translated to their negative representations, while still being an
edge in the trie.
