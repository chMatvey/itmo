#define referenceFlag "--reference"
#define delimiter "="
#define recursive "R"
#define someInfo "v"

typedef struct {
    char* source;
    char* dest;
    int* flags;
} parsedArgs;

parsedArgs parse();