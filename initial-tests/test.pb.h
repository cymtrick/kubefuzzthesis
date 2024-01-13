// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_test_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_test_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_test_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_test_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_test_2eproto;
class TEST;
struct TESTDefaultTypeInternal;
extern TESTDefaultTypeInternal _TEST_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::TEST* Arena::CreateMaybeMessage<::TEST>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class TEST final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:TEST) */ {
 public:
  inline TEST() : TEST(nullptr) {}
  ~TEST() override;
  explicit PROTOBUF_CONSTEXPR TEST(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  TEST(const TEST& from);
  TEST(TEST&& from) noexcept
    : TEST() {
    *this = ::std::move(from);
  }

  inline TEST& operator=(const TEST& from) {
    CopyFrom(from);
    return *this;
  }
  inline TEST& operator=(TEST&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TEST& default_instance() {
    return *internal_default_instance();
  }
  static inline const TEST* internal_default_instance() {
    return reinterpret_cast<const TEST*>(
               &_TEST_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(TEST& a, TEST& b) {
    a.Swap(&b);
  }
  inline void Swap(TEST* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TEST* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TEST* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<TEST>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const TEST& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const TEST& from) {
    TEST::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(TEST* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "TEST";
  }
  protected:
  explicit TEST(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBFieldNumber = 2,
    kAFieldNumber = 1,
  };
  // required string b = 2;
  bool has_b() const;
  private:
  bool _internal_has_b() const;
  public:
  void clear_b();
  const std::string& b() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_b(ArgT0&& arg0, ArgT... args);
  std::string* mutable_b();
  PROTOBUF_NODISCARD std::string* release_b();
  void set_allocated_b(std::string* b);
  private:
  const std::string& _internal_b() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_b(const std::string& value);
  std::string* _internal_mutable_b();
  public:

  // required uint32 a = 1;
  bool has_a() const;
  private:
  bool _internal_has_a() const;
  public:
  void clear_a();
  uint32_t a() const;
  void set_a(uint32_t value);
  private:
  uint32_t _internal_a() const;
  void _internal_set_a(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:TEST)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr b_;
    uint32_t a_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_test_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// TEST

// required uint32 a = 1;
inline bool TEST::_internal_has_a() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool TEST::has_a() const {
  return _internal_has_a();
}
inline void TEST::clear_a() {
  _impl_.a_ = 0u;
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline uint32_t TEST::_internal_a() const {
  return _impl_.a_;
}
inline uint32_t TEST::a() const {
  // @@protoc_insertion_point(field_get:TEST.a)
  return _internal_a();
}
inline void TEST::_internal_set_a(uint32_t value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.a_ = value;
}
inline void TEST::set_a(uint32_t value) {
  _internal_set_a(value);
  // @@protoc_insertion_point(field_set:TEST.a)
}

// required string b = 2;
inline bool TEST::_internal_has_b() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool TEST::has_b() const {
  return _internal_has_b();
}
inline void TEST::clear_b() {
  _impl_.b_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& TEST::b() const {
  // @@protoc_insertion_point(field_get:TEST.b)
  return _internal_b();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void TEST::set_b(ArgT0&& arg0, ArgT... args) {
 _impl_._has_bits_[0] |= 0x00000001u;
 _impl_.b_.Set(static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:TEST.b)
}
inline std::string* TEST::mutable_b() {
  std::string* _s = _internal_mutable_b();
  // @@protoc_insertion_point(field_mutable:TEST.b)
  return _s;
}
inline const std::string& TEST::_internal_b() const {
  return _impl_.b_.Get();
}
inline void TEST::_internal_set_b(const std::string& value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.b_.Set(value, GetArenaForAllocation());
}
inline std::string* TEST::_internal_mutable_b() {
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.b_.Mutable(GetArenaForAllocation());
}
inline std::string* TEST::release_b() {
  // @@protoc_insertion_point(field_release:TEST.b)
  if (!_internal_has_b()) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* p = _impl_.b_.Release();
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.b_.IsDefault()) {
    _impl_.b_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return p;
}
inline void TEST::set_allocated_b(std::string* b) {
  if (b != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.b_.SetAllocated(b, GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (_impl_.b_.IsDefault()) {
    _impl_.b_.Set("", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:TEST.b)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_test_2eproto
