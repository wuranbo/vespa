// Copyright 2016 Yahoo Inc. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.
#pragma once

#include <vector>
#include <vespa/document/fieldvalue/fieldvalue.h>
#include "result.h"

namespace document {
namespace select {

class ResultList : public Printable {
public:
    typedef FieldValue::IteratorHandler::VariableMap VariableMap;
    typedef std::pair<VariableMap, const Result*> ResultPair;
    typedef std::vector<ResultPair> Results;
    typedef Results::iterator iterator;
    typedef Results::const_iterator const_iterator;

    ResultList();
    ResultList(ResultList &&) = default;
    ResultList & operator = (ResultList &&) = default;
    ~ResultList();

    /**
       Creates a result list with one element with the given result type and no parameters.
    */
    explicit ResultList(const Result& result);

    void add(const VariableMap& variables, const Result& result);

    ResultList operator&&(const ResultList& other) const;
    ResultList operator||(const ResultList& other) const;
    ResultList operator!() const;

    void print(std::ostream& out, bool verbose, const std::string& indent) const override;

    bool isEmpty() const { return _results.empty(); }

    const Result& combineResults() const;

    bool operator==(const ResultList& other) const;

    const Results& getResults() const { return _results; }
    Results& getResults() { return _results; }
    const_iterator begin() const { return _results.begin(); }
    const_iterator end() const { return _results.end(); }
    iterator begin() { return _results.begin(); }
    iterator end() { return _results.end(); }

private:
    Results _results;
    bool combineVariables(VariableMap& output, const FieldValue::IteratorHandler::VariableMap& input) const;
};

inline bool operator==(const ResultList& list, const Result& other) {
    return (list.combineResults() == other);
}

inline bool operator!=(const ResultList& list, const Result& other) {
    return (list.combineResults() != other);
}

}
}

