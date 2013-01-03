/*
  Copyright (c) 2012 Matthew Stump

  This file is part of libcql.

  libcql is free software; you can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  libcql is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CQL_HEADER_H_
#define CQL_HEADER_H_

#include <iomanip>
#include <istream>
#include <ostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "cql.h"
#include "util.hpp"

namespace cql {
namespace internal {

#pragma pack(push, 1)
class cql_header_t {

public:

	cql_header_t() :
		_version(0),
		_flags(0),
		_stream(0),
		_opcode(0),
		_length(0)
	{}

	cql_header_t(cql_byte_t version,
				 cql_byte_t flags,
				 cql_byte_t stream,
				 cql_byte_t opcode,
				 cql_int_t length) :
		_version(version),
		_flags(flags),
		_stream(stream),
		_opcode(opcode),
		_length(length)
	{}

	std::string
	str() const
	{
		std::stringstream output;
		output << std::setfill('0');
		output << "{version: 0x" << std::setw(2) << cql::internal::hex(_version);
		output << ", flags: 0x" << std::setw(2) << cql::internal::hex(_flags);
		output << ", stream: 0x" << std::setw(2) << cql::internal::hex(_stream);
		output << ", opcode: 0x" << std::setw(2) << cql::internal::hex(_opcode);
		output << ", length: " << boost::lexical_cast<std::string>(_length) << "}";
		return output.str();
	}

	std::ostream&
	write(std::ostream& output) const
	{
		output.put(_version);
		output.put(_flags);
		output.put(_stream);
		output.put(_opcode);

		cql_int_t l = htonl(_length);
		output.write(reinterpret_cast<char*>(&l), sizeof(l));
		return output;
	}

	std::istream&
	read(std::istream& input)
	{
		_version = input.get();
		_flags = input.get();
		_stream = input.get();
		_opcode = input.get();
		input.read(reinterpret_cast<char*>(&_length), sizeof(_length));
		_length = ntohl(_length);
		return input;
	}

    cql_int_t
	size() const
	{
		return sizeof(_version) + sizeof(_flags) + sizeof(_stream) + sizeof(_opcode) + sizeof(_length);
    }

	cql_byte_t
	version() const
	{
		return _version;
	}

	cql_byte_t
	flags() const
	{
		return _flags;
	}

	cql_byte_t
	stream() const
	{
		return _stream;
	}

	cql_byte_t
	opcode() const
	{
		return _opcode;
	}

	cql_int_t
	length() const
	{
		return _length;
	}

	void
	version(cql_byte_t v)
	{
		_version = v;
	}

	void
	flags(cql_byte_t v)
	{
		_flags = v;
	}

	void
	stream(cql_byte_t v)
	{
		_stream = v;
	}

	void
	opcode(cql_byte_t v)
	{
	    _opcode = v;
	}

	void
	length(cql_int_t v)
	{
		_length = v;
	}

	friend std::ostream
	&operator<<(std::ostream& output,
				const cql_header_t& h)
	{
		output << h.str();
        return output;
    }

private:
	cql_byte_t  _version;
	cql_byte_t  _flags;
	cql_byte_t   _stream;
	cql_byte_t  _opcode;
	cql_int_t  _length;
};
#pragma pack(pop)


} // namespace internal
} // namespace cql

#endif // CQL_HEADER_H_
