#include<stdio.h>
#include<windows.h>//don't break this approch
#include<mmsystem.h>//use -lwinmm linker with gcc
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<conio.h>

#define N "\x1b[0m"
#define X "\x1b[5m"
#define R "\x1b[31m"
#define G "\x1b[32m"
#define B "\x1b[34m"
#define BY "\x1b[43m"

void sub();
void print(char*);
void ex(char*);
void plyStart(char*);
void plyStop();
int check();
void storeToFile();
void loadFromFile();
void registerUser();
void displayUsers();
void loginUser();
void insert();
void deleteElement();
void show();
void nextPathly();
void prePly();
void firstPathly();
void lastPathly();
void specifictitle();
void backupPlaylist(char*);
void restorePlaylist(char*);
void sub2(char*);

struct User{
    char uName[25];
    char pass[25];
    struct User* next;
};

struct Ply{
    char title[50];
    char path[70];
    struct Ply* next;
    struct Ply* pre;
};

struct User* head = NULL;
char tTitle[50],tPath[70];
struct Ply* head2 = NULL;
struct Ply* c=NULL;

void print(char *s)
{   
    int c_delay=50,s_delay=100,n_delay=150;
    for (int i = 0; s[i] != '\0'; i++)
    {
        printf("%c", s[i]);
        fflush(stdout);
        if (s[i] == ' ')
        {
            usleep(s_delay * 1000); 
        }
        else if (s[i] == '\n')
        {
            usleep(n_delay * 1000); 
        }
        else
        {
            usleep(c_delay * 1000); 
        }
    }
}

void plyStart(char* filename) {
  char command[100];
  sprintf(command, "open %s type mpegvideo alias mp3", filename); 
  mciSendString(command, NULL, 0, NULL); 
  mciSendString("play mp3", NULL, 0, NULL); 
}

void plyStop() {
  mciSendString("stop mp3", NULL, 0, NULL); 
  mciSendString("close mp3", NULL, 0, NULL); 
}

int check() {
    char status[256];
    mciSendString("status mp3 mode", status, sizeof(status), NULL);

    if (strstr(status, "playing") != NULL) {
        return 1;
    } else {
        return 0;
    }
}

void storeToFile() {
    FILE* file = fopen("catch.dat", "w");
    if (file != NULL) {
        struct User* current = head;
        while (current != NULL) {
            fprintf(file, "%s %s\n", current->uName, current->pass);
            current = current->next;
        }
        fclose(file);
    }
}

void loadFromFile() {
    FILE* file = fopen("catch.dat", "r");
    if (file != NULL) {
        char uName[25], pass[25];
        while (fscanf(file, "%s %s", uName, pass) == 2) {
            struct User* newUser = (struct User*)malloc(sizeof(struct User));
            if (newUser == NULL) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return;
            }

            strcpy(newUser->uName, uName);
            strcpy(newUser->pass, pass);
            newUser->next = NULL;

            newUser->next = head;
            head = newUser;
        }
        fclose(file);
    } 
}

void registerUser() {
    char uName[25], pass[25], cPass[25];

    print("Enter username ? ");
    scanf("%s", uName);

    struct User* current = head;
    while (current != NULL) {
        if (strcmp(current->uName, uName) == 0) {
            printf(X R BY"Username already exists. Please choose a different username."N B BY);
            getch();
            return;
        }
        current = current->next;
    }

    print("Enter password ? ");
    scanf("%s", pass);

    print("Confirm password ? ");
    scanf("%s", cPass);

    if (strcmp(pass, cPass) != 0) {
        printf(X R BY"Password and confirm password do not match. Registration failed."N B BY);
        system(X R BY"pause"N B BY);
        return;
    }

    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    if (newUser == NULL) {
        printf(X R BY"Memory allocation failed.\n"N B BY);
        getch();
        return;
    }

    strcpy(newUser->uName, uName);
    strcpy(newUser->pass, pass);
    newUser->next = NULL;

    newUser->next = head;
    head = newUser;
    FILE* file = fopen(uName, "w");
    fclose(file);
    print(X G"Registration successfully."N B BY);
    getch();
}

void displayUsers() {
    struct User* current = head;
    print("\nRegistered Users:\n");
    while (current != NULL) {
        printf("Username: %s\n", current->uName);
        current = current->next;
    }
    printf("\n");
    print(X G"Press enter to continue..."N B BY);
    getch();
}

void loginUser() {
    char uName[25], pass[25];
    print("Enter username ? ");
    scanf("%s", uName);
    print("Enter password ? ");
    scanf("%s", pass);

    struct User* current = head;
    while (current != NULL) {
        if (strcmp(current->uName, uName) == 0 && strcmp(current->pass, pass) == 0) {
            printf(X G"Login successful."N B BY);
            getch();
            sub2(uName);
        }
        current = current->next;
    }

    printf(X R BY"Invalid username or password. Login failed."N B BY);
    getch();
}

void insert() {
    print("Enter Music Name ? ");
    while ((getchar()) != '\n');
    scanf("%[^\n]%*c", tTitle);

    struct Ply *check_ptr = head2;
    while (check_ptr != NULL) {
        if (strcmp(check_ptr->title, tTitle) == 0) {
            printf(X R BY"Music with the same title already exists. Please choose a different title."N B BY);
            getch();
            return;
        }
        check_ptr = check_ptr->next;
    }

    struct Ply *new_Ply = (struct Ply *)malloc(sizeof(struct Ply));
    strcpy(new_Ply->title, tTitle);

    print('Enter specific (full) .mp3 path in Double-quotas [exmaple : "C:\windows32\Yash\Desktop\New folder\beep.mp3" ] ? ');
    scanf("%[^\n]%*c", new_Ply->path);
    
    if (head2 == NULL) {
        new_Ply->next = new_Ply->pre = new_Ply;
        head2 = c = new_Ply;
    } else {
        struct Ply *last = head2->pre;
        new_Ply->pre = last;
        last->next = new_Ply;
        new_Ply->next = head2;
        head2->pre = new_Ply;
    }
    print(X G"Song added..."N B BY);
    getch();
}

void deleteElement() {
    if (head2 == NULL) {
        printf(X R BY"No Music is there to delete!"N B BY);
        getch();
        return;
    }

    print("Enter Music Name to delete ? \n");
    while ((getchar()) != '\n')
        ;
    scanf("%[^\n]%*c", tTitle);

    struct Ply *ptr = head2;

    do {
        if (ptr->next == ptr && strcmp(ptr->title, tTitle) == 0) {
            printf(X G"One file deleted! Playlist is Empty Now!"N B BY);
            head2 = NULL;
            free(ptr);
            getch();
            return;
        } else if (strcmp(ptr->title, tTitle) == 0) {
            struct Ply *pre = ptr->pre;
            struct Ply *next = ptr->next;
            pre->next = next;
            next->pre = pre;

            if (ptr == c) {
                c = next;
            }

            if (ptr == head2) {
                head2 = next;
            }

            free(ptr);
            printf(X G"Music deleted!"N B BY);
            getch();
            return;
        }

        ptr = ptr->next;

    } while (ptr != head2);

    printf("No Music file is there!\n");
}

void show() {
    if (head2 == NULL) {
        printf(X R BY"Playlist is Empty!"N B BY);
        getch();
        return;
    }

    struct Ply *show_ptr = head2;
    int i = 1;

    printf("\nDisplaying Playlist:\n");

    do {
        printf("Song %d : %s\n", i, show_ptr->title);
        i++;
        show_ptr = show_ptr->next;
    } while (show_ptr != head2);
    getch();
}

void nextPathly() {
    if (c == NULL) {
        printf(X R BY"No songs in Playlist!"N B BY);
        getch();
        return;
    }

    c = c->next;

    if (c != NULL) {
        printf(X G"Playing Next Song: %s"N BY B, c->title);
        plyStop();
        plyStart(c->path);
    }
    getch();
}

void prePly() {
    if (c == NULL) {
        printf(X R BY"No songs in Playlist!"N B BY);
        getch();
        return;
    }

    c = c->pre;

    if (c != NULL) {
        printf(X G"Playing preious Song: %s"N BY B, c->title);
        plyStop();
        plyStart(c->path);
    }
    getch();
}

void firstPathly() {
    if (head2 == NULL) {
        printf(X R BY"Playlist is Empty!"N B BY);
        getch();
        return;
    }

    printf(X G"Playing First Music: %s"N BY B, head2->title);

    if (check() == 0) {
        plyStop();
        plyStart(head2->path);
    }
    getch();
}

void lastPathly() {
    if (head2 == NULL) {
        printf(X R BY"Playlist is Empty!"N B BY);
        getch();
        return;
    }

    printf("Playing Last Music: %s\n", head2->pre->title);

    if (check() == 0) {
        plyStop();
        plyStart(head2->pre->path);
    }
    getch();
}

void specifictitle() {
    if (head2 == NULL) {
        printf(X R BY"No music is there to be searched!"N B BY);
        getch();
        return;
    }

    printf("Enter Music Name to search:\n");
    while ((getchar()) != '\n')
        ;
    scanf("%[^\n]%*c", tTitle);

    struct Ply *ptr = head2;

    do {
        if (strcmp(ptr->title, tTitle) == 0) {
            print("Music Found!\n");
            printf(X G"Playing Music: %s"N B BY, ptr->title);

            if (check() == 0) {
                plyStop();
                plyStart(ptr->path);
            }
            getch();
            return;
        }

        ptr = ptr->next;

    } while (ptr != head2);

    printf("\n"X R BY"There is no Music file with this name!"N B BY);
    getch();
}

void backupPlaylist(char* uName) {
    FILE *file = fopen(uName, "w");

    struct Ply *ptr = head2;

    if (head2 != NULL) {
        do {
            fprintf(file, "%s|%s\n", ptr->title, ptr->path);
            ptr = ptr->next;
        } while (ptr != head2);
    }

    fclose(file);
}

void restorePlaylist(char* uName) {
    FILE *file = fopen(uName, "r");

    char line[100];

    while (fgets(line, sizeof(line), file) != NULL) {
        struct Ply *new_Ply = (struct Ply *)malloc(sizeof(struct Ply));

        sscanf(line, "%[^|]|%[^\n]", new_Ply->title, new_Ply->path);

        if (head2 == NULL) {
            new_Ply->next = new_Ply->pre = new_Ply;
            head2 = c = new_Ply;
        } else {
            struct Ply *last = head2->pre;
            new_Ply->pre = last;
            last->next = new_Ply;
            new_Ply->next = head2;
            head2->pre = new_Ply;
        }
    }

    fclose(file);
}

void sub2(char* uName){
    int choice;
    storeToFile();
    restorePlaylist(uName); 
    do {
        system("cls");
        printf("-------------------------------------------\n");
        printf("            Welcome,%s\n",uName);
        printf("-------------------------------------------\n");
        printf("\n######         User panel          ######\n");
        printf("1. Add Music\n");
        printf("2. Remove Music\n");
        printf("3. Show Playlist\n");
        printf("4. Play next file\n");
        printf("5. Play previous file\n");
        printf("6. Play first file\n");
        printf("7. Play Last file\n");
        printf("8. Play specific file\n");
        printf("9. Exit\n");
        printf("0. Pause any music\n\n");
        print("Enter your choice ? ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            insert();
            backupPlaylist(uName);
            break;

        case 2:
            deleteElement();
            backupPlaylist(uName);
            break;

        case 3:
            show();
            break;

        case 4:
            nextPathly();
            break;

        case 5:
            prePly();
            break;

        case 6:
            firstPathly();
            break;

        case 7:
            lastPathly();
            break;

        case 8:
            specifictitle();
            break;

        case 9:
            ex(uName);
            break;

        case 0:
            plyStop();
            break;

        default:
            printf(X R BY"Invalid choice. Please try again."N B BY);
            getch();
        }
        
    } while (1);

    
}

void sub(){
    int c;
    do{
        system("cls");
        printf("\n##############################################");
        printf("\n############      Welcome     ################");
        printf("\n############ *to music plyer  ################");
        printf("\n##############################################");
        printf("\n1.Register\n2.Login\n3.Show users\n4.Exit\n\n");
        print("Enter your choice ? ");
        scanf("%d",&c);
        switch (c){
            case 1:registerUser();
            break;
            case 2:loginUser();
            break;
            case 3:displayUsers();
            system(X G"pause"N B BY);
            break;
            case 4:
            ex(NULL);
            break;
            default:
            printf(X R BY"Invalid choice. Please try again.\n"N B BY);
            getch();
        }

    }while(1);
}

void ex(char* uName) {
    char c;
    do {
        system("cls");
        printf(R BY"Dear %s, do you really want to exit (y / n) ? "N B BY, uName);
        scanf(" %c", &c);  // Note the space before %c to consume any leading whitespace

        switch (c) {
            case 'n':
            case 'N':
                return;
                break;
            case 'y':
            case 'Y':
                break;
            default:
                printf(X R BY"Invalid choice. Please try again.\n"N B BY);
                getch();
        }
    } while (c != 'y' && c != 'Y');

    print(" Thnk Uhh! for using our software... ");
    storeToFile();
    backupPlaylist(uName);
    getch();
    exit(0);
}

int main(){
    printf(B BY);
    loadFromFile();
    sub();
    return 0;
}
