#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

struct Row_t {
    uint32_t id; // unsigned 32 bit integer
    char username[COLUMN_USERNAME_SIZE + 1]; // varchar(32) plus null char
    char email[COLUMN_EMAIL_SIZE + 1]; // varchar(255) plus null char
};

typedef struct Row_t Row;

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ROW_SIZE =
        size_of_attribute(Row, id)
        + size_of_attribute(Row, username)
        + size_of_attribute(Row, email);

/**
 * Header layout.
 *
 * const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
 * const uint32_t NODE_TYPE_OFFSET = 0;
 * const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
 * const uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
 * const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
 * const uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
 * const uint8_t COMMON_NODE_HEADER_SIZE =
        +    NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;
 *
 */
const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
const uint32_t NODE_TYPE_OFFSET = 0;
const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
const uint32_t IS_ROOT_OFFSET = sizeof(uint8_t);
const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
const uint32_t PARENT_POINTER_OFFSET = sizeof(uint8_t) + sizeof(uint8_t);
const uint8_t COMMON_HEADER_SIZE = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t);

/**
 * Leaf layout.
 *
 * const uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
 * const uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
 * const uint32_t LEAF_NODE_HEADER_SIZE =
 *   COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE;
 */
const uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
const uint32_t LEAF_NODE_NUM_CELLS_OFFSET =
        sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t);
const uint32_t LEAF_NODE_HEADER_SIZE =
        sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint32_t);

/**
 * Layout for node body.
 *
 * const uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
 * const uint32_t LEAF_NODE_KEY_OFFSET = 0;
 * const uint32_t LEAF_NODE_VALUE_SIZE = ROW_SIZE;
 * const uint32_t LEAF_NODE_VALUE_OFFSET =
 *     LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;
 * const uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;
 * const uint32_t LEAF_NODE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_NODE_HEADER_SIZE;
 * const uint32_t LEAF_NODE_MAX_CELLS =
 *     LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;
 */
const uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
const uint32_t LEAF_NODE_KEY_OFFSET = 0;
const uint32_t LEAF_NODE_VALUE_SIZE = size_of_attribute(Row, id)
                                      + size_of_attribute(Row, username)
                                      + size_of_attribute(Row, email);
const uint32_t LEAF_NODE_VALUE_OFFSET = 0
                                        + size_of_attribute(Row, id)
                                        + size_of_attribute(Row, username)
                                        + size_of_attribute(Row, email);
const uint32_t LEAF_NODE_CELL_SIZE = sizeof(uint32_t)
                                     + size_of_attribute(Row, id)
                                     + size_of_attribute(Row, username)
                                     + size_of_attribute(Row, email);
const uint32_t LEAF_NODE_SPACE_FOR_CELLS =
        PAGE_SIZE
        - sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint32_t);
const uint32_t LEAF_NODE_MAX_CELLS =
        +PAGE_SIZE
        - sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint32_t)
        / sizeof(uint32_t)
        + size_of_attribute(Row, id)
        + size_of_attribute(Row, username)
        + size_of_attribute(Row, email);

const uint32_t USERNAME_OFFSET =
        (0 + size_of_attribute(Row, id));
const uint32_t EMAIL_OFFSET =
        (0 + size_of_attribute(Row, id)) // username offset
        + size_of_attribute(Row, username);

uint32_t* leaf_node_num_cells(void* node) {
  return node + LEAF_NODE_KEY_OFFSET;
}

void* leaf_node_cell(void* node, uint32_t cell_num) {
  return node + LEAF_NODE_HEADER_SIZE + cell_num + LEAF_NODE_KEY_SIZE;
}

uint32_t* leaf_node_key(void* node, uint32_t cell_num) {
  return leaf_node_cell(node, cell_num);
}

void* leaf_node_value(void* node, uint32_t cell_num) {
  return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}

void initialize_leaf_node(void* node){
  *leaf_node_num_cells(node) = 0;
}
