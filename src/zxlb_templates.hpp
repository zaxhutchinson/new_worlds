#pragma once

#include<limits>

#include<vector>
#include<cstdint>
#include<memory>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<string>
#include<queue>
#include<variant>
#include<optional>
#include<list>

#define FMT_HEADER_ONLY
#include<fmt/core.h>
#include<fmt/format.h>
#include<fmt/os.h>
#include<fmt/color.h>

#include"sole.hpp"

template<typename T>
using vec = std::vector<T>;
template<typename T>
using uptr = std::unique_ptr<T>;
template<typename T>
using sptr = std::shared_ptr<T>;
template<typename T>
using wptr = std::weak_ptr<T>;
template<typename T>
using vuptr = vec<uptr<T>>;
template<typename T>
using vsptr = vec<sptr<T>>;
template<typename T>
using vwptr = vec<wptr<T>>;
template<typename T, typename U>
using umap = std::unordered_map<T,U>;
template<typename T, typename U>
using pair = std::pair<T,U>;
template<typename T>
using uset = std::unordered_set<T>;
template<typename T>
using que = std::queue<T>;
using str = std::string;
template<typename T>
using opt = std::optional<T>;
template<typename T>
using vopt = vec<opt<T>>;
template<typename T>
using lst = std::list<T>;
template<typename T>
using luptr = lst<uptr<T>>;
using strv = std::string_view;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using sizet = std::size_t;

using ID = str;
using UUID = sole::uuid;