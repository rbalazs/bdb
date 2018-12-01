/*
 * uint32_t is a numeric type that guarantees to be 32 bits,
 * unsigned, meaning that the range of values goes from 0 to 2^32-1
 *                                                          (4.294.967.295)
 * 'Bout the row:
 *   column	   size (bytes)	offset
 *   id	       4	          0
 *   username	 32	          4
 *   email	   255	        36
 * total: 291
*/

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

struct Row_t {
  uint32_t id; // unsigned 32 bit integer
  char username[COLUMN_USERNAME_SIZE]; // varchar(32)
  char email[COLUMN_EMAIL_SIZE]; // varchar(255)
};

typedef struct Row_t Row;

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ROW_SIZE =
  size_of_attribute(Row, id)
  + size_of_attribute(Row, username)
  + size_of_attribute(Row, email);

const uint32_t USERNAME_OFFSET =
  (0 + size_of_attribute(Row, id));

const uint32_t EMAIL_OFFSET =
  (0 + size_of_attribute(Row, id)) // username offset
  + size_of_attribute(Row, username);

void serialize_row(Row* source, void* destination) {
  memcpy(destination + 0, &(source->id), ID_SIZE);
  memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
  memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row (void* source, Row* destination) {
  memcpy(&(destination->id), source + 0, ID_SIZE);
  memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void print_row(Row* row) {
  printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}
