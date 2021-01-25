#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// make constants for max data length and max no rows
#define MAX_DATA 512
#define MAX_ROWS 100


//Struct for adress
struct Address {
    //id
    int id;
    //flag to see if address is set
    int set;
    //char field with length of max data
    char name[MAX_DATA];
    //char field with length of max data
    char email[MAX_DATA];
};

//Struct for db
struct Database {
    //Make no of rows in db
    struct Address rows[MAX_ROWS];
};

//Connection struct
struct Connection {
    //Declare file as a File 
    FILE* file;
    //Address to db
    struct Database* db;
};

//Function for closing connedction to db
void Database_close(
    /*Takes pointer to Connection struct as param*/struct Connection* conn)
{
    //If there is a conn
    if(conn) {
        //If file i set close file
        if(conn->file) fclose(conn->file);
        //if conn db is set free up the memory
        if(conn->db) free(conn->db);
        //free up the struct
        free(conn);
    }
}

//Error handling function
void die(const char* message,struct Connection *conn)
{   
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    Database_close(conn);

    exit(1);
}

//Print address function
void Address_print(/*Pointer to adress struct*/struct Address* addr)
{
    printf("%d %s %s \n",
    addr->id,addr->name, addr->email);
}

void Address_find_name(struct Connection* conn,const char* name)
{
    int i = 0;
    
    //Get db from conn and store in Database struct pointer
    struct Database* db = conn->db;

    //Loop over
    for(i = 0; i < MAX_ROWS; i++){
        //get the current ith record
        struct Address* cur = &db->rows[i];
        if(!strcmp(cur->name,name)){
            Address_print(cur);
        }
    }
}

//Load Database function
void Database_load(
    /*takes connection pointer as arg*/struct Connection* conn)
{   
    //vad gör fread?
    int rc = fread(
        /*hämta db adress från conn*/conn->db, 
        /*hämta storlek på db*/sizeof(struct Database), 
        /**/1,
        /*Vilken fil ska db läsa ifrån*/conn->file);
    //If rc didnt load run die with msg
    if(rc != 1) die("Failed to load database.",conn);
}

//struct Connection
/*returns pointer to conn struct*/struct Connection* Database_open(const char* filename, char mode)
{
    //allocate memory for struct of type connection and
    //store address in conn
    struct Connection* conn = malloc(sizeof(struct Connection));
    //if memory has not been allocated throw error
    if(!conn) die("Memory error",conn);

    //allocate memory for database in conn and store
    //in db field of connection struct
    conn->db = malloc(sizeof(struct Database));
    //If db of conn is not set throw error
    if(!conn->db) die("Memory error",conn);

    //If the mode specified with CLI is c
    //access file file field of conn struct
    // and use fopen on it with write mode = create new file
    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    //Otherwise use read mode
    }else {
        conn-> file = fopen(filename, "r+");

        //If the file is set in conn struct run
        //Database_load with conn as parameter
        if(conn->file){
            Database_load(conn);
        }
    }

    //If there is no file throw error
    if(!conn->file) die("Failed to open the file",conn);

    //return the connection poiter
    return conn;
}



//Function for writing to database
void Database_write(
    /*Takes pointer to connection struct*/struct Connection* conn)
{
    //The rewind() function sets the file position indicator for the 
    //stream pointed to by stream to the beginning of the file. 
    rewind(conn->file);

    //Store result of fwrite in rc
    //returns This function returns the total number of elements successfully 
    //returned as a size_t object, which is an integral data type. 
    //If this number differs from the nmemb parameter, it will show an error.
    //fwrite takes pointer to db
    //the size of each element to be written
    //the number of elements
    //and the output stream i.e where to write
    int rc = fwrite(conn->db,sizeof(struct Database),1, conn->file);
    //if rc is not equal to 1 see above
    //throw error
    if(rc != 1) die("Failed to write to databse",conn);

    //fflush clears the output buffer
    //returns 0 if succesful
    rc = fflush(conn->file);
    //If rc is -1
    //throw an error
    if(rc == -1) die("Cannot flush database",conn);
}

//Function to create database
void Database_create(
    /*Takes pointer to conn struct*/struct Connection *conn)
{
    //Declare i and set to 0
    int i = 0;

    //loop over i for max number of rows
    for(i = 0; i < MAX_ROWS; i++) {
        //make an address struct and set id to
        //i and flag as not written in
        struct Address addr = {.id = i, .set = 0};
        //Add address to db in row i
        conn->db->rows[i] = addr;
    }
}

//Function for setting databse record
void Database_set(
    /*Pointer to conn struct*/ struct Connection* conn,
    /*id of record to be set*/ int id, 
    /*name of record to be set*/ const char* name,
    /*email of record to be set*/ const char* email)
{
    //Address to specific row
    struct Address* addr = &conn->db->rows[id];
    //if the record is already set throw error
    if(addr->set) die("Already set, delete it first",conn);

    //set the set flag of the record loaded to 1
    addr->set = 1;
    
    //Copy the value of name to the loaded
    //records name field and make sure it is
    //not bigger/longer than the specified max data value
    char* res = strncpy(addr->name,name, MAX_DATA);
    //Set the last character to '\0' to fix strncpy bug
    addr->name[MAX_DATA-1] = '\0';
    //if we can not set res throw error
    if(!res) die("Name copy failed",conn); 

    //see above
    res = strncpy(addr->email,email, MAX_DATA);
    addr->email[MAX_DATA-1] = '\0';
    if(!res) die("Email copy failed",conn);
}

//Function to get record with id
void Database_get(
    /*Pointer to connection struct*/struct Connection* conn, 
    /*id to find*/int id)
{
    //Get address of record with provided id 
    struct Address* addr = &conn->db->rows[id];

    //If the record is set
    if(addr->set) {
        //then print the record
        Address_print(addr);
    }
    //Otherwise throw error
    else {
        die("ID is not set",conn);
    }
}

//Function to delete record with id
void Database_delete(struct Connection* conn, int id)
{
    //Make a blank record
    struct Address addr = {.id = id, .set = 0};
    //and set the specifed record to be this blank record
    conn->db->rows[id] = addr;
}

//Function to list all records in db
void Database_list(
    /*Takes pointer to connection*/struct Connection* conn)
{
    int i = 0;
    
    //Get db from conn and store in Database struct pointer
    struct Database* db = conn->db;

    //Loop over
    for(i = 0; i < MAX_ROWS; i++){
        //get the current ith record
        struct Address* cur = &db->rows[i];
        //and if it is set
        if(cur->set) {
            //print it out
            Address_print(cur);
        }

    }
}

//Main 
int main(int argc, char* argv[])
{
    //If there is less than 3 arg provided as cli
    //throw an error
    if(argc <3 ) die("USAGE: ex17 <dbfile><action> [action params]",NULL);

    //The first arg is the filename
    char* filename = argv[1];
    //first charachter of 2nd is mode
    char action = argv[2][0];
    //Run Database open with filename and action
    //provided as arg ans stor as pointer to a
    //Connection struct
    struct Connection* conn = Database_open(filename,action);
    
    //Declare id and set to 0
    int id = 0;

    //If more than 3 args at cli set
    //arg 3 to id
    //atoi parses the string and intrprets content as integral number
    if(argc > 3) id = atoi(argv[3]);
    //If the id is larger than max rows in db
    //throw an error
    if(id >= MAX_ROWS) die("There is not that many records in the db",conn);

    //Switch menu on arg provided with action
    switch(action) {
        case 'f':
            Address_find_name(conn,argv[4]);
            break;
        //if 'create'
        case 'c':
            //create a db
            Database_create(conn);
            //and write to file
            Database_write(conn);
            break;
        //if case is 'get'
        case 'g':
            //If id is not provided as arg
            //throw an error
            if(argc !=4) die("Need an ID to use get",conn);

            //Get record with id from db
            Database_get(conn,id);
            break;
        //if case is 'set'
        case 's':
            //If 6 args is not provided
            //throw an error
            if(argc !=6) die("Need id, name and email to set",conn);
            //Set record in db with name and email provided at cli
            Database_set(conn,id,argv[4], argv[5]);
            //write to file
            Database_write(conn);
            break;
        //if case is 'delete
        case 'd':
            //If 4 args is not provided
            //throw an error
            if(argc != 4) die("Need to specify ID to delete",conn);
            //Delete id from record in db
            Database_delete(conn,id);
            //write to file
            Database_write(conn);
        //if case is 'list'
        case 'l':
            //list all records in db
            Database_list(conn);
            break;

        default:
            //default action trows error if case not above
            die("invalid action. Use c= create, g=get, s= set, d= delete or l= list",conn);
            
            }

        

            return 0;
}

