#pragma once
#include <cstdint>
#include <bitset>
#include <memory>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;
using Signature = std::bitset<32>;

constexpr Entity MAX_ENTITIES = 5000;
constexpr ComponentType MAX_COMPONENTS = 32;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}