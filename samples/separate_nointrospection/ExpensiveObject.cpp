// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#include "TodayObjects.h"

#include "graphqlservice/introspection/Introspection.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std::literals;

namespace graphql::today {
namespace object {

Expensive::Expensive()
	: service::Object({
		"Expensive"
	}, {
		{ R"gql(order)gql"sv, [this](service::ResolverParams&& params) { return resolveOrder(std::move(params)); } },
		{ R"gql(__typename)gql"sv, [this](service::ResolverParams&& params) { return resolve_typename(std::move(params)); } }
	})
{
}

service::FieldResult<response::IntType> Expensive::getOrder(service::FieldParams&&) const
{
	throw std::runtime_error(R"ex(Expensive::getOrder is not implemented)ex");
}

std::future<service::ResolverResult> Expensive::resolveOrder(service::ResolverParams&& params)
{
	std::unique_lock resolverLock(_resolverMutex);
	auto directives = std::move(params.fieldDirectives);
	auto result = getOrder(service::FieldParams(std::move(params), std::move(directives)));
	resolverLock.unlock();

	return service::ModifiedResult<response::IntType>::convert(std::move(result), std::move(params));
}

std::future<service::ResolverResult> Expensive::resolve_typename(service::ResolverParams&& params)
{
	return service::ModifiedResult<response::StringType>::convert(response::StringType{ R"gql(Expensive)gql" }, std::move(params));
}

} /* namespace object */

void AddExpensiveDetails(std::shared_ptr<schema::ObjectType> typeExpensive, const std::shared_ptr<schema::Schema>& schema)
{
	typeExpensive->AddFields({
		schema::Field::Make(R"gql(order)gql"sv, R"md()md"sv, std::nullopt, schema->WrapType(introspection::TypeKind::NON_NULL, schema->LookupType("Int")))
	});
}

} /* namespace graphql::today */