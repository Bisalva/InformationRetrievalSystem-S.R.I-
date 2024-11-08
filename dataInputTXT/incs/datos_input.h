
//lista de los archivos 
typedef struct Nodo {
    char *nombre_archivo;
    char *contenido;
    struct Nodo *siguiente;
} Nodo;

//PROTOTIPOS
int verificar_extension_archivo(const char *nombre_archivo);
char* leer_archivo(const char *archivo);
Nodo* agregar_nodo(Nodo *inicio, const char *nombre_archivo, const char *contenido);
void liberar_memoria(Nodo *inicio);


