#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int HashTable_Size = 5;
char last_id[5+1] = "-----";

struct Mahasiswa{
    char nama[50+1];
    char email[20+1];
    char pass[30+1];
    char gender[6+1];
    int umur;
    float saldo;
    char id[5+1];
    struct Mahasiswa *next;
} *head[HashTable_Size], *tail[HashTable_Size];

void menu(int *choice){
    for(;;){// endless loop
        system("CLS || clear"); //buat clear screen
        puts("Menu Hash Function");
        puts("1. Mid-Square");
        puts("2. Division");
        puts("3. Folding");
        puts("4. Digit Extraction");
        puts("5. Custom");
        printf(">> "); scanf("%d", &(*choice)); getchar();
    
        if(*choice >= 1 && *choice <= 5){
            break;
        }
    }
}

int calculate_total_ASCII(char string[]){
    int len = strlen(string);
    int sum = 0;
    for(int i=0; i<len; i++){
        sum += string[i];
    }
    return sum;
}

long long int exponent(int num, int exponent_num){
    long long int result = 1;
    for(int i=0; i<exponent_num; i++){
        result *= num;
    }
    return result;
}

int get_digit(int num){
    int digit = 0;
    while(num != 0){
        num /= 10;
        digit++;
    }
    return digit;
}

int hashFunction_MidSquare(char input[]){
    long long int total_ASCII = calculate_total_ASCII(input);
    total_ASCII *= total_ASCII; //dikuadratin
    // printf("hasil kuadrat: %d\n", total_ASCII);

    int digit = get_digit(total_ASCII);
    int size_digit = get_digit(HashTable_Size);

    int start_digit = (digit - size_digit)/2;
    total_ASCII /= exponent(10, start_digit); //123 4567 890 -> 123 4567 (dihapus)
    // printf("current total ascii: %d\n", total_ASCII);
    if(digit % 2 == 0 && size_digit % 2 != 0){ //genap
        size_digit++; //misal digit = 3 dan length ada 10 -> 1234567890 jadi 123 4567 890, bukan 123 456 7890 atau 1234 567 890
    }
    else if(digit % 2 == 1 && size_digit % 2 != 1){ //ganjil
        size_digit++;
    }

    // printf("%d %d\n", exponent(10, 1), total_ASCII %= exponent(10, 1));
    total_ASCII %= exponent(10, size_digit);
    // printf("index: %d\n", total_ASCII);
    return total_ASCII % HashTable_Size;
}

int hashFunction_Division(char input[]){
    int total_ASCII = calculate_total_ASCII(input);
    return (total_ASCII % HashTable_Size);
}

int hashFunction_Folding(char input[]){
    int total_ASCII = calculate_total_ASCII(input); //ex: 123456789, size = 20 (2 digit)
    int size_digit = get_digit(HashTable_Size);

    int modulo = exponent(10, size_digit);
    int index = 0;
    while(total_ASCII != 0){
        index += total_ASCII % modulo;
        total_ASCII /= modulo;
    } //result: 1+23+45+67+89 = 225

    printf("Folding Index: %d\n", index);
    return index % HashTable_Size; //return 225 % 20 = 5
}

int hashFunction_DigitExtraction(char input[], int n_separator){ //if n_separator = 2 -> 123456789 -> 3+ 6 + 9
    int total_ASCII = calculate_total_ASCII(input); //ex: 123456789, size = 20 (2 digit)

    int index = 0;
    int divider = exponent(10, n_separator+1);
    while(total_ASCII != 0){
        index += total_ASCII % 10;
        total_ASCII /= divider;
    }
    printf("Extract Index: %d\n", index);
    return index % HashTable_Size;
}

int hashFunction_Custom(char input[]){
    int index;
    if(input[0] >= 'a' && input[0] <= 'z'){
        index = input[0] - 'a' + 1;
    }
    else if(input[0] >= 'A' && input[0] <= 'Z'){
        index = input[0] - 'A' + 1;
    }
    else{ //for symbols
        index = 0;
    }

    // printf("Custom Index: %d\n", index);
    return index % HashTable_Size;
}


int Hash_Function(int choice_function, char input[]){
    if(choice_function == 1){
        return hashFunction_MidSquare(input);
    }
    else if(choice_function == 2){
        return hashFunction_Division(input);
    }
    else if(choice_function == 3){
        return hashFunction_Folding(input);
    }
    else if(choice_function == 4){
        return hashFunction_DigitExtraction(input, 2);
    }
    else if(choice_function == 5){
        return hashFunction_Custom(input);
    }
}

char random_char(){
    int urutan = rand() % 26; //26 size abjad
    return urutan + 'A';
}

char random_int(){
    int urutan = rand() % 10; //10 size angka
    return urutan + '0';
}

char go_back_str(char str[]){
    if(strcmp(str, "0") == 0){
        return '1'; //kembali ke menu utama
    }
}

char go_back_int(int integer){
    if(integer == 0){
        return '1'; //kembali ke menu utama
    }
}

char go_back_float(float digit){
    if(digit == 0.0){
        return '1'; //kembali ke menu utama
    }
}

char validate_nama(char nama[]){
    int len = strlen(nama);
    int letter = 0, words = 1;
    for(int i=0; i<len; i++){
        if(nama[i] == ' '){
            if(letter < 3){
                break;
            }

            words++;
            letter = 0;
        }
        else{
            letter++;
        }
    }
    if(letter < 3){
        puts("Tiap kata harus mengandung minimal 3 karakter selain spasi!\n");
    }
    else if(words < 2){
        puts("Nama minimal harus terdiri dari 2 kata!\n");
    }
    else{
        return '1';
    }
    return '0';
}

char validate_email(char email[]){
    int len = strlen(email);
    char validator[9+1] = "@univ.com";
    for(int i=8, j=len-1; i>=0; i--, j--){
        if(validator[i] != email[j]){
            puts("Email harus berakhiran @univ.com!\n");
            return '0';
        }
        if(i == 0){
            return '1';
        }
    }
}

char validate_pass(char pass[]){
    int len = strlen(pass);
    char flag_besar, flag_kecil, flag_angka, flag_simbol;
    flag_besar = flag_kecil = flag_angka = flag_simbol = '0';
    for(int i=0; i<len; i++){
        if(pass[i] >= 'A' && pass[i] <= 'Z'){
            flag_besar = '1';
        }
        else if(pass[i] >= 'a' && pass[i] <= 'z'){
            flag_kecil = '1';
        }
        else if(pass[i] >= '0' && pass[i] <= '9'){
            flag_angka = '1';
        }
        else{
            flag_simbol = '1';
        }
    }

    if(flag_besar == '0' || flag_kecil == '0' || flag_angka == '0' || flag_simbol == '0'){
        puts("Password harus memiliki huruf besar, huruf kecil, angka, dan simbol\n");
        return '0';
    }
    else{
        return '1';
    }
}

char validate_gender(char gender[]){
    if(strcmpi(gender, "Pria") == 0 || strcmpi(gender, "Wanita") == 0){
        return '1';
    }
    else{
        puts("Gender harus antara Pria atau Wanita!\n");
        return '0';
    }
}

char validate_umur(int umur){
    if(umur >= 18 && umur <= 70){
        return '1';
    }
    else{
        puts("Anda terlalu muda/tua\n");
        return '0';
    }
}

char validate_saldo(float saldo){
    if(saldo < 0.0){
        puts("Saldo harus diatas 0\n");
        return '0';
    }
    else{
        return '1';
    }
}

void add_orang(int choice_function){

    //Bikin Node baru beserta inisialisasi isinya
    struct Mahasiswa *orang_baru = (struct Mahasiswa *) malloc(sizeof(struct Mahasiswa));
    for(;;){
        printf("Isi nama: "); scanf("%[^\n]", orang_baru->nama); getchar();

        if(go_back_str(orang_baru->nama) == '1'){
            return;
        }
        if(validate_nama(orang_baru->nama) == '1'){
            break;
        }
    }
    for(;;){
        printf("Isi email: "); scanf("%[^\n]", orang_baru->email); getchar();

        if(go_back_str(orang_baru->email) == '1'){
            return;
        }
        if(validate_email(orang_baru->email) == '1'){
            break;
        }
    }
    for(;;){
        printf("Isi pass: "); scanf("%[^\n]", orang_baru->pass); getchar();

        if(go_back_str(orang_baru->pass) == '1'){
            return;
        }
        if(validate_pass(orang_baru->pass) == '1'){
            break;
        }
    }
    for(;;){
        printf("Isi gender [Pria || Wanita]: "); scanf("%[^\n]", orang_baru->gender); getchar();

        if(go_back_str(orang_baru->gender) == '1'){
            return;
        }
        if(validate_gender(orang_baru->gender) == '1'){
            break;
        }
    }
    for(;;){
        printf("Isi umur: "); scanf("%d", &(orang_baru->umur)); getchar();

        if(go_back_int(orang_baru->umur) == '1'){
            return;
        }
        if(validate_umur(orang_baru->umur) == '1'){
            break;
        }
    }
    for(;;){
        printf("Isi Saldo: "); scanf("%f", &(orang_baru->saldo)); getchar();

        if(go_back_float(orang_baru->saldo) == '1'){
            return;
        }
        if(validate_saldo(orang_baru->saldo) == '1'){
            break;
        }
    }

    if(strcmp(last_id, "-----") == 0){//pertama
        for(int i=0; i<5; i++){
            if(i >= 0 && i <= 1){
                last_id[i] = random_char();
            }
            else if(i >= 2 && i <= 4){
                last_id[i] = random_int();
            }
        }
    }
    else{//bukan pertama
        for(int i=4; i>=0; i--){
            if(last_id[i] == '9' || last_id[i] == 'Z'){
                last_id[i] = '0';
            }
            else{
                last_id[i]++;
            }
        }
    }
    strcpy(orang_baru->id, last_id);

    orang_baru->next = NULL;


    //Masukin ke Linked List di Hash Table
    int index = Hash_Function(choice_function, orang_baru->nama);
    if(head[index] == NULL){ //pushFirst
        head[index] = orang_baru;
        tail[index] = orang_baru;
    }
    else{
        if(strcmp(orang_baru->nama, head[index]->nama) < 0){ //pushHead
            orang_baru->next = head[index];
            head[index] = orang_baru;
        }
        else if(strcmp(orang_baru->nama, tail[index]->nama) > 0){ //pushTail
            tail[index]->next = orang_baru;
            tail[index] = orang_baru;
        }
        else{ //pushMid
            struct Mahasiswa *inspectur1 = head[index]->next;
            struct Mahasiswa *inspectur2 = head[index];
            while(inspectur1 != NULL){
                if(strcmp(inspectur1->nama, orang_baru->nama) > 0){
                    break;
                }
                inspectur2 = inspectur1;
                inspectur1 = inspectur1->next;
            }
            orang_baru->next = inspectur1;
            inspectur2->next = orang_baru;
        }
    }
}

int main_menu(){
    int pilihan;
    for(;;){// endless loop
        system("CLS || clear"); //buat clear screen
        puts("Menu Utama");
        puts("1. Tambah Orang");
        puts("2. Lihat Data");
        puts("3. Hapus Orang");
        puts("4. Ubah Saldo");
        puts("5. Hapus Semua Data");
        puts("0. Tutup Program");
        printf(">> "); scanf("%d", &pilihan); getchar();
    
        if(pilihan >= 0 && pilihan <= 5){
            break;
        }
    }
    return pilihan;
}

void tampil_data(struct Mahasiswa *orang){
    printf("Nama: %s\n", orang->nama);
    printf("Email: %s\n", orang->email);
    printf("Pass: %s\n", orang->pass);
    printf("Gender: %s\n", orang->gender);
    printf("Umur: %d\n", orang->umur);
    printf("Saldo: %.2f\n", orang->saldo);
    // printf("ID: %s\n", orang_baru->id));
    puts("");
}

void print(){
    for(int i=0; i<HashTable_Size; i++){
        printf("Linked-List Index %d:\n", i);
        struct Mahasiswa *inspectur = head[i];
        while(inspectur != NULL){
            tampil_data(inspectur);
            inspectur = inspectur->next;
        }
    }
}

void remove_orang(int choice_hashFunction){
    char target_nama[50+1];
    printf("Nama yang dihapus: "); scanf("%[^\n]", target_nama); getchar();
    int index = Hash_Function(choice_hashFunction, target_nama);

    if(head[index] == NULL){
        printf("Nama tidak ada!");
        return;
    }
    else{
        if(strcmp(head[index]->nama, target_nama) == 0){ //popHead
            if(head[index] == tail[index]){ //tinggal sendirian (popOne)
                free(head[index]);
                head[index] = NULL;
                tail[index] = NULL;
            }
            else{ //popHead
                struct Mahasiswa *inspectur = head[index];
                head[index] = head[index]->next;
                inspectur->next = NULL;
                free(inspectur);
            }
        }
        else if(strcmp(tail[index]->nama, target_nama) == 0){ //popTail
            struct Mahasiswa *inspectur = head[index];
            while(inspectur != NULL){
                if(inspectur->next == tail[index]){
                    break;
                }
                inspectur = inspectur->next;
            }
            tail[index] = inspectur;
            free(tail[index]->next);
            tail[index]->next = NULL;
        }
        else{ //popMid
            struct Mahasiswa *inspectur1 = head[index];
            struct Mahasiswa *inspectur2 = NULL;
            while(inspectur1 != NULL){
                if(strcmp(inspectur1->nama, target_nama) == 0){
                    break;
                }
                inspectur2 = inspectur1;
                inspectur1 = inspectur1->next;
            }
            if(inspectur1 == NULL){
                printf("Nama tidak ada!");
                return;
            }

            //namanya ada
            inspectur2->next = inspectur1->next;
            inspectur1->next = NULL;
            free(inspectur1);
        }
    }
}


void update_saldo(int choice_hashFunction){
    char target_nama[50+1];
    printf("Nama yang mau diupdate saldonya: "); scanf("%[^\n]", target_nama); getchar();
    int index = Hash_Function(choice_hashFunction, target_nama);
    
    if(head[index] == NULL){
        printf("Nama tidak ada!");
        return;
    }
    else{
        struct Mahasiswa *inspectur = head[index];
        while(inspectur != NULL){
            if(strcmp(inspectur->nama, target_nama) == 0){
                break;
            }
            inspectur = inspectur->next;
        }
        if(inspectur == NULL){
            printf("Nama tidak ada!");
            return;
        }
        
        tampil_data(inspectur);
        float perubahan_saldo = 0;
        printf("Penambahan Saldo: "); scanf("%f", &perubahan_saldo); getchar();
        inspectur->saldo += perubahan_saldo;
        printf("Saldo akhir: %.2f\n", inspectur->saldo);
    }
}

void remove_all(){
    for(int i=0; i<HashTable_Size; i++){
        while(head[i] != NULL){ //popHead
            if(head[i] == tail[i]){ //tinggal sendirian (popOne)
                free(head[i]);
                head[i] = NULL;
                tail[i] = NULL;
            }
            else{ //popHead
                struct Mahasiswa *inspectur = head[i];
                head[i] = head[i]->next;
                inspectur->next = NULL;
                free(inspectur);
            }
        }
    }
}

void enter_to_continue(){
    printf("\nEnter to Continue.."); getchar();
}
     

int main(){
    srand(time(0));
    int choice_hashFunction;
    menu(&choice_hashFunction);

    for(;;){ //endless loop
        int choice_menu = main_menu();
        
        switch(choice_menu){
            case 1: //tambah orang
                add_orang(choice_hashFunction);
                break;
            case 2: //print
                print();
                enter_to_continue();
                break;
            case 3: //remove
                remove_orang(choice_hashFunction);
                enter_to_continue();
                break;
            case 4: //update
                update_saldo(choice_hashFunction);
                enter_to_continue();
                break;
            case 5: //hapus semua
                remove_all();
                break;
            case 0: //exit
                return 0;
                break;
        }
    }
}

/*
Abdi
Abdi Ab
Abdi Abdul
123456789012345678901
12345678901234567890
abdi@univ.com
1234567890123456789012345678901
12345678901234567890123456789
1234567890123456789012345678A
123456789012345678901234567Aa
Halo 123
pri
pria
17
71
70
-1
123.455

---------------------------------

1
Abdi Abdul
abdi@univ.com
Halo 123
pria
70
123.455
1
Budi Antonius
budi@univ.com
Halo 321
pria
19
123000
1
Awe Sasa
awe@univ.com
hihi123 Spasi
wanita
58
0.01
1
Aang 123
ang@univ.com
hihi123 Spasi
pria
58
0.1
1
Ani Michelle
ani@univ.com
hihi123 Spasi
wanita
54
123134.3212
*/