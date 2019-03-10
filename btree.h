enum NodeType_t {
    NODE_INTERNAL,
    NODE_LEAF
};

typedef enum NodeType_t NodeType;

const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
const uint32_t NODE_TYPE_OFFSET = 0;
const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
const uint32_t IS_ROOT_OFFSET = sizeof(uint8_t);
const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
const uint32_t PARENT_POINTER_OFFSET = sizeof(uint8_t) + sizeof(uint8_t);
const uint8_t COMMON_HEADER_SIZE = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t);
