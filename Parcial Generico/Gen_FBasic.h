
typedef struct
{
    int id;
    char nombre[51];
    char apellido[51];
    float salario;
    int sector;
    int estado;
} eGenerica;


int generica_inicializar (eGenerica*, int);

void generica_inicializarConDatos (eGenerica*, int);

int generica_buscarEspacio (eGenerica*, int);

int generica_encontrarPorId (eGenerica*, int, int);

void generica_mostrarUno (eGenerica);

int generica_mostrarTodos (eGenerica*, int);

int generica_idAutoIncremental (eGenerica*, int);

int generica_alta (eGenerica*, int);

int generica_baja (eGenerica*, int);

int generica_modificacion (eGenerica*, int);

int generica_menuModificacion (eGenerica*, int);

int generica_ordenar (eGenerica*, int, int);
