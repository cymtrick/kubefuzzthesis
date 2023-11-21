// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

// Author: petar@google.com (Petar Petrov)

#ifndef GOOGLE_PROTOBUF_PYTHON_CPP_DESCRIPTOR_H__
#define GOOGLE_PROTOBUF_PYTHON_CPP_DESCRIPTOR_H__

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "google/protobuf/descriptor.h"

namespace google {
namespace protobuf {
namespace python {

extern PyTypeObject PyMessageDescriptor_Type;
extern PyTypeObject PyFieldDescriptor_Type;
extern PyTypeObject PyEnumDescriptor_Type;
extern PyTypeObject PyEnumValueDescriptor_Type;
extern PyTypeObject PyFileDescriptor_Type;
extern PyTypeObject PyOneofDescriptor_Type;
extern PyTypeObject PyServiceDescriptor_Type;
extern PyTypeObject PyMethodDescriptor_Type;

// Wraps a Descriptor in a Python object.
// The C++ pointer is usually borrowed from the global DescriptorPool.
// In any case, it must stay alive as long as the Python object.
// Returns a new reference.
PyObject* PyMessageDescriptor_FromDescriptor(const Descriptor* descriptor);
PyObject* PyFieldDescriptor_FromDescriptor(const FieldDescriptor* descriptor);
PyObject* PyEnumDescriptor_FromDescriptor(const EnumDescriptor* descriptor);
PyObject* PyEnumValueDescriptor_FromDescriptor(
    const EnumValueDescriptor* descriptor);
PyObject* PyOneofDescriptor_FromDescriptor(const OneofDescriptor* descriptor);
PyObject* PyFileDescriptor_FromDescriptor(
    const FileDescriptor* file_descriptor);
PyObject* PyServiceDescriptor_FromDescriptor(
    const ServiceDescriptor* descriptor);
PyObject* PyMethodDescriptor_FromDescriptor(
    const MethodDescriptor* descriptor);

// Alternate constructor of PyFileDescriptor, used when we already have a
// serialized FileDescriptorProto that can be cached.
// Returns a new reference.
PyObject* PyFileDescriptor_FromDescriptorWithSerializedPb(
    const FileDescriptor* file_descriptor, PyObject* serialized_pb);

// Return the C++ descriptor pointer.
// This function checks the parameter type; on error, return NULL with a Python
// exception set.
const Descriptor* PyMessageDescriptor_AsDescriptor(PyObject* obj);
const FieldDescriptor* PyFieldDescriptor_AsDescriptor(PyObject* obj);
const EnumDescriptor* PyEnumDescriptor_AsDescriptor(PyObject* obj);
const FileDescriptor* PyFileDescriptor_AsDescriptor(PyObject* obj);
const ServiceDescriptor* PyServiceDescriptor_AsDescriptor(PyObject* obj);

// Returns the raw C++ pointer.
const void* PyDescriptor_AsVoidPtr(PyObject* obj);

// Check that the calling Python code is the global scope of a _pb2.py module.
// This function is used to support the current code generated by the proto
// compiler, which insists on modifying descriptors after they have been
// created.
//
// stacklevel indicates which Python frame should be the _pb2.py module.
//
// Don't use this function outside descriptor classes.
bool _CalledFromGeneratedFile(int stacklevel);

bool InitDescriptor();

}  // namespace python
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_PYTHON_CPP_DESCRIPTOR_H__