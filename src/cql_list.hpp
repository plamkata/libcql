/*
  Copyright (c) 2013 Matthew Stump

  This file is part of libcql.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef CQL_LIST_H_
#define CQL_LIST_H_

#include <vector>
#include "libcql/cql.h"

namespace cql {

    class cql_list_t
    {

    public:
        cql_list_t(
            cql_byte_t*        start,
            cql_int_t          element_type,
            const std::string& custom_class);

        std::string
        str() const;

        cql_int_t
        element_type() const;

        const std::string&
        custom_class() const;

        bool
        get_bool(
            size_t i,
            bool& output) const;

        bool
        get_int(
            size_t i,
            cql_int_t& output) const;

        bool
        get_float(
            size_t i,
            float& output) const;

        bool
        get_double(
            size_t i,
            double& output) const;

        bool
        get_bigint(
            size_t i,
            cql_bigint_t& output) const;

        bool
        get_string(
            size_t i,
            std::string& output) const;

        bool
        get_data(
            size_t i,
            cql_byte_t** output,
            cql_short_t& size) const;

        size_t
        size() const;

    private:
        cql_byte_t*              _start;
        std::vector<cql_byte_t*> _elements;
        cql_int_t                _element_type;
        std::string              _custom_class;
    };

} // namespace cql

#endif // CQL_LIST_H_
