# generated from rosidl_generator_py/resource/_idl.py.em
# with input from object_information_msgs_ros2:msg/Object.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Object(type):
    """Metaclass of message 'Object'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('object_information_msgs_ros2')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'object_information_msgs_ros2.msg.Object')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__object
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__object
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__object
            cls._TYPE_SUPPORT = module.type_support_msg__msg__object
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__object

            from geometry_msgs.msg import Pose
            if Pose.__class__._TYPE_SUPPORT is None:
                Pose.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Object(metaclass=Metaclass_Object):
    """Message class 'Object'."""

    __slots__ = [
        '_header',
        '_detect_sequence',
        '_object_total',
        '_object_sequence',
        '_label',
        '_probability',
        '_position',
        '_size',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'detect_sequence': 'uint64',
        'object_total': 'uint16',
        'object_sequence': 'uint16',
        'label': 'string',
        'probability': 'float',
        'position': 'geometry_msgs/Pose',
        'size': 'geometry_msgs/Vector3',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Pose'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.detect_sequence = kwargs.get('detect_sequence', int())
        self.object_total = kwargs.get('object_total', int())
        self.object_sequence = kwargs.get('object_sequence', int())
        self.label = kwargs.get('label', str())
        self.probability = kwargs.get('probability', float())
        from geometry_msgs.msg import Pose
        self.position = kwargs.get('position', Pose())
        from geometry_msgs.msg import Vector3
        self.size = kwargs.get('size', Vector3())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.detect_sequence != other.detect_sequence:
            return False
        if self.object_total != other.object_total:
            return False
        if self.object_sequence != other.object_sequence:
            return False
        if self.label != other.label:
            return False
        if self.probability != other.probability:
            return False
        if self.position != other.position:
            return False
        if self.size != other.size:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def detect_sequence(self):
        """Message field 'detect_sequence'."""
        return self._detect_sequence

    @detect_sequence.setter
    def detect_sequence(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'detect_sequence' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'detect_sequence' field must be an unsigned integer in [0, 18446744073709551615]"
        self._detect_sequence = value

    @builtins.property
    def object_total(self):
        """Message field 'object_total'."""
        return self._object_total

    @object_total.setter
    def object_total(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'object_total' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'object_total' field must be an unsigned integer in [0, 65535]"
        self._object_total = value

    @builtins.property
    def object_sequence(self):
        """Message field 'object_sequence'."""
        return self._object_sequence

    @object_sequence.setter
    def object_sequence(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'object_sequence' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'object_sequence' field must be an unsigned integer in [0, 65535]"
        self._object_sequence = value

    @builtins.property
    def label(self):
        """Message field 'label'."""
        return self._label

    @label.setter
    def label(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'label' field must be of type 'str'"
        self._label = value

    @builtins.property
    def probability(self):
        """Message field 'probability'."""
        return self._probability

    @probability.setter
    def probability(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'probability' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'probability' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._probability = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if __debug__:
            from geometry_msgs.msg import Pose
            assert \
                isinstance(value, Pose), \
                "The 'position' field must be a sub message of type 'Pose'"
        self._position = value

    @builtins.property
    def size(self):
        """Message field 'size'."""
        return self._size

    @size.setter
    def size(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'size' field must be a sub message of type 'Vector3'"
        self._size = value
