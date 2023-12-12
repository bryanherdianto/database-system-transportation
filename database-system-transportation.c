/*
Semua rumus dan tingkat kategori berdasarkan sumber-sumber berikut:
1. https://duitpintar.com/mobil-paling-irit-bbm/
2. https://www.researchgate.net/publication/301678822_Prediction_of_CO_CO2_CH4_and_N2O_vehicle_emissions_from_environmental_impact_assessment_EIA_at_toll_road_of_Krian-Legundi-Bunder_in_East_Java_of_Indonesia
3. https://www.oto.com/berita-motor/10-pilihan-sepeda-motor-paling-irit-bbm-ada-yang-tembus-60-km-per-liter
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>

#define SIZE 1000
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// membuat tipe data enum
typedef enum Conditions
{
    equal,
    bigger,
    smaller,
    bigger_equal,
    smaller_equal
} conditions;

typedef enum SudahDihitung
{
    sudah,
    belum
} sudah_dihitung;

// membuat tipe data struct
typedef struct Kendaraan
{
    char kategori[SIZE];
    char bahan_bakar[SIZE];
    char nama[SIZE];
    float jarak_tempuh;
    float konsumsi_bahan_bakar;
    float jumlah_emisi[4];
} kendaraan;

typedef struct ArraySorting
{
    char nama[SIZE];
    float nilai;
} array_sorting;

// function declaration
void display_sdg();
void display_menu_home();
void display_menu_analisis_visualisasi(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_input(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_search(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_petunjuk_program();
void display_tentang_program();
void display_data(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_std(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_var(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_sum(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_edit(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_max(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_min(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_countif(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_count_kedua(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_count_pertama(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_histogram(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
void display_menu_sortir(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
int count_data(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[]);
int count_if_data_str(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[], int input_count, char str_condition[]);
int count_if_data_int(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[], int input_count, conditions kondisi, char str_condition[]);
void sorting(array_sorting array[], int jumlah_keluarga);
float max_data(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], int jumlah_keluarga, int jumlah_kendaraan[], int input_max);
float min_data(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], int jumlah_keluarga, int jumlah_kendaraan[], int input_min);
void make_histogram(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[], int input_hist, char **model_mobil, int size_model);
char *to_lower(char *s);
int adalah_angka(char *s);
int is_repeated(char **s, char new[]);
void hitung_emisi(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], int jumlah_keluarga, int jumlah_kendaraan[]);
void hitung_sum(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], float sum[], int jumlah_keluarga, int jumlah_kendaraan[], int input_olah_data);
void hitung_variansi(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], float sum[], float variansi[], int jumlah_keluarga, int jumlah_kendaraan[], int input_olah_data);
void hitung_std_deviasi(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], float sum[], float variansi[], float std_deviasi[], int jumlah_keluarga, int jumlah_kendaraan[], int input_olah_data);

int main()
{
    // inisialisasi variabel
    int size_model = 0, input_home, input_menu, i, j, k, jumlah_keluarga = 0, tambahan_keluarga, input_hist, jumlah_kendaraan[SIZE], input_analisis, next, pos_kendaraan, pos_keluarga, input_sortir, input_edit, input_olah_data, input_search, input_count, input_min, input_max, kategori_pemborosan_mobil[4], kategori_pemborosan_motor[3], kategori_sustainable_mobil[2], kategori_sustainable_motor[2];
    float koef_emisi[3][4] = {{2.59786, 0.00004, 0.46263, 0.00071}, {2.59786, 0.00007, 0.42705, 0.00356}, {2.92490, 0.00016, 0.01186, 0.00008}};
    float sum[6], std_deviasi[6], variansi[6], min, max, editan_f;
    char condition_pertama[SIZE], condition_kedua[SIZE], editan_str[SIZE], temp_str[SIZE];

    // inisialisasi sebuah array yang terdiri dari string
    char **model_mobil = malloc(SIZE * sizeof(char *));
    for (i = 0; i < SIZE; i++)
    {
        *(model_mobil + i) = malloc(SIZE * sizeof(char));
    }

    // inisialisasi variabel tipe data struct
    kendaraan **data_kendaraan_rumah_tangga = malloc(sizeof(kendaraan *));

    // error handling apabila pointer null
    for (i = 0; i < SIZE; i++)
    {
        if (*(model_mobil + i) == NULL)
        {
            printf("Alokasi memori tidak berhasil\nProgram akan restart...\n");
            Sleep(2000);
            main();
        }
    }
    if (model_mobil == NULL)
    {
        printf("Alokasi memori tidak berhasil\nProgram akan restart...\n");
        Sleep(2000);
        main();
    }

    // error handling apabila pointer null
    if (data_kendaraan_rumah_tangga == NULL)
    {
        printf("Alokasi memori tidak berhasil\nProgram akan restart...\n");
        Sleep(2000);
        main();
    }

    // inisialisasi variabel tipe data enum
    conditions kondisi = bigger;
    sudah_dihitung dihitung = belum;

    // print tampilan awal
    display_sdg();
    printf("\nJudul:\n");
    printf("Sistem Database dan Perhitungan Pemborosan Energi dalam Kasus Penggunaan Alat Transportasi dalam Rumah Tangga\n\n");
    printf("KELOMPOK 3 - SIMALAKAMA\n");
    printf("Anggota:\n");
    printf("   1. Adi Nugroho \t\t\t 2306208546\n");
    printf("   2. Bryan Herdianto \t\t\t 2306210885\n");
    printf("   3. Muhammad Riyan Satrio Wibowo \t 2306229323\n");
    printf("   4. Syahmi Hamdani \t\t\t 2306220532\n\n");
    printf("Klik '1' untuk memulai program... ");
    scanf("%d", &next);

    // print menu home
    display_menu_home();
    scanf("%d", &input_home);

    // program akan terus loop sampai user input exit program
    while (input_home != 5)
    {
        if (input_home == 1)
        {
            display_menu_input(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
            scanf("%d", &input_menu);

            while (input_menu != 4)
            {
                // menu input data
                switch (input_menu)
                {
                case 1:
                    // pilihan input data
                    printf("Mau input berapa data? ");
                    scanf("%d", &tambahan_keluarga);

                    printf("\nSILAKAN INPUT %d DATA\n", tambahan_keluarga);

                    data_kendaraan_rumah_tangga = realloc(data_kendaraan_rumah_tangga, (jumlah_keluarga + tambahan_keluarga) * sizeof(kendaraan *));

                    for (i = jumlah_keluarga; i < jumlah_keluarga + tambahan_keluarga; i++)
                    {
                        printf("=============================================");
                        printf("\nDATA KELUARGA KE-%d : ", i + 1);

                        printf("\nMasukkan jumlah kendaraan\t: ");
                        scanf(" %[^\n]s", &temp_str);

                        // error handling
                        while (!adalah_angka(temp_str))
                        {
                            printf(ANSI_COLOR_RED "Belum benar... tolong diulang\t: " ANSI_COLOR_RESET);
                            scanf(" %[^\n]s", &temp_str);
                        }
                        jumlah_kendaraan[i] = atoi(temp_str);

                        *(data_kendaraan_rumah_tangga + i) = malloc(jumlah_kendaraan[i] * sizeof(kendaraan));

                        // error handling apabila pointer null
                        if (*(data_kendaraan_rumah_tangga + j) == NULL)
                        {
                            printf("Alokasi memori tidak berhasil\nProgram akan restart...\n");
                            Sleep(2000);
                            main();
                        }

                        for (j = 0; j < jumlah_kendaraan[i]; j++)
                        {
                            // i merujuk ke keluarga ke berapa dan j merujuk pada kendaraan ke berapa pada keluarga tersebut
                            printf("\tINPUT KENDARAAN KE-%d\n", j + 1);

                            printf("\tKategori kendaraan (mobil/motor)\t\t: ");
                            scanf(" %s", &data_kendaraan_rumah_tangga[i][j].kategori);
                            strcpy(data_kendaraan_rumah_tangga[i][j].kategori, to_lower(data_kendaraan_rumah_tangga[i][j].kategori));

                            // error handling
                            while (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "mobil", 5) != 0 && strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "motor", 5) != 0)
                            {
                                printf(ANSI_COLOR_RED "\tBelum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                                scanf(" %s", &data_kendaraan_rumah_tangga[i][j].kategori);
                                strcpy(data_kendaraan_rumah_tangga[i][j].kategori, to_lower(data_kendaraan_rumah_tangga[i][j].kategori));
                            }

                            if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "mobil", 5) == 0)
                            {
                                printf("\tBahan bakar (bensin/solar/elektrik)\t\t: ");
                                scanf(" %s", &data_kendaraan_rumah_tangga[i][j].bahan_bakar);
                                strcpy(data_kendaraan_rumah_tangga[i][j].bahan_bakar, to_lower(data_kendaraan_rumah_tangga[i][j].bahan_bakar));

                                // error handling
                                while (strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "bensin", 20) != 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "solar", 20) != 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "elektrik", 20) != 0)
                                {
                                    printf(ANSI_COLOR_RED "\tBelum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                                    scanf(" %s", &data_kendaraan_rumah_tangga[i][j].bahan_bakar);
                                    strcpy(data_kendaraan_rumah_tangga[i][j].bahan_bakar, to_lower(data_kendaraan_rumah_tangga[i][j].bahan_bakar));
                                }
                            }
                            else if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "motor", 5) == 0)
                            {
                                printf("\tBahan bakar (bensin/elektrik)\t\t\t: ");
                                scanf(" %s", &data_kendaraan_rumah_tangga[i][j].bahan_bakar);
                                strcpy(data_kendaraan_rumah_tangga[i][j].bahan_bakar, to_lower(data_kendaraan_rumah_tangga[i][j].bahan_bakar));

                                // error handling
                                while (strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "bensin", 20) != 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "elektrik", 20) != 0)
                                {
                                    printf(ANSI_COLOR_RED "\tBelum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                                    scanf(" %s", &data_kendaraan_rumah_tangga[i][j].bahan_bakar);
                                    strcpy(data_kendaraan_rumah_tangga[i][j].bahan_bakar, to_lower(data_kendaraan_rumah_tangga[i][j].bahan_bakar));
                                }
                            }

                            printf("\tModel kendaraan\t\t\t\t\t: ");
                            scanf(" %[^\n]s", &data_kendaraan_rumah_tangga[i][j].nama);
                            strcpy(data_kendaraan_rumah_tangga[i][j].nama, to_lower(data_kendaraan_rumah_tangga[i][j].nama));

                            // mendapatkan semua input yang unik
                            if (!is_repeated(model_mobil, data_kendaraan_rumah_tangga[i][j].nama))
                            {
                                model_mobil[size_model] = data_kendaraan_rumah_tangga[i][j].nama;
                                size_model++;
                            }

                            printf("\tJarak tempuh (dalam satuan km)\t\t\t: ");
                            scanf(" %[^\n]s", &temp_str);

                            // error handling
                            while (!adalah_angka(temp_str))
                            {
                                printf(ANSI_COLOR_RED "\tBelum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                                scanf(" %[^\n]s", &temp_str);
                            }
                            data_kendaraan_rumah_tangga[i][j].jarak_tempuh = atof(temp_str);

                            if (strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "elektrik", 20) != 0)
                            {
                                printf("\tKonsumsi bahan bakar (dalam satuan L/km)\t: ");
                                scanf("%f", &data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar);
                            }
                            else
                            {
                                data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar = 0;
                            }

                            puts("");
                        }
                    }

                    // update dihitung jadi belum supaya tidak bisa akses opsi sortir
                    dihitung = belum;

                    jumlah_keluarga += tambahan_keluarga;

                    break;
                case 2:
                    // pilihan hapus data
                    printf("Urutan keluarga mana yang mau diedit? ");
                    scanf(" %[^\n]s", &temp_str);

                    while (!adalah_angka(temp_str))
                    {
                        printf(ANSI_COLOR_RED "Belum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                        scanf(" %[^\n]s", &temp_str);
                    }
                    pos_keluarga = atoi(temp_str);

                    printf("Urutan kendaraan mana yang mau diedit? ");
                    scanf(" %[^\n]s", &temp_str);

                    while (!adalah_angka(temp_str))
                    {
                        printf(ANSI_COLOR_RED "Belum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                        scanf(" %[^\n]s", &temp_str);
                    }
                    pos_kendaraan = atoi(temp_str);

                    if (jumlah_kendaraan[pos_keluarga - 1] == 1)
                    {
                        for (i = pos_keluarga - 1; i < jumlah_keluarga - 1; i++)
                        {
                            *(data_kendaraan_rumah_tangga + i) = realloc(*(data_kendaraan_rumah_tangga + i), jumlah_kendaraan[i + 1] * sizeof(kendaraan));

                            for (j = 0; j < jumlah_kendaraan[i + 1]; j++)
                            {
                                data_kendaraan_rumah_tangga[i][j] = data_kendaraan_rumah_tangga[i + 1][j];
                            }
                        }
                    }
                    else
                    {
                        for (j = pos_kendaraan - 1; j < jumlah_kendaraan[pos_keluarga - 1] - 1; j++)
                        {
                            data_kendaraan_rumah_tangga[i][j] = data_kendaraan_rumah_tangga[i][j + 1];
                        }
                    }

                    jumlah_keluarga--;

                    break;

                case 3:
                    // pilihan edit data
                    display_menu_edit(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    scanf("%d", &input_edit);

                    printf("Urutan keluarga mana yang mau diedit? ");
                    scanf(" %[^\n]s", &temp_str);

                    while (!adalah_angka(temp_str))
                    {
                        printf(ANSI_COLOR_RED "Belum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                        scanf(" %[^\n]s", &temp_str);
                    }
                    pos_keluarga = atoi(temp_str);

                    printf("Urutan kendaraan mana yang mau diedit? ");
                    scanf(" %[^\n]s", &temp_str);

                    while (!adalah_angka(temp_str))
                    {
                        printf(ANSI_COLOR_RED "Belum benar... tolong diulang\t\t\t: " ANSI_COLOR_RESET);
                        scanf(" %[^\n]s", &temp_str);
                    }
                    pos_kendaraan = atoi(temp_str);

                    if (input_edit == 1)
                    {
                        printf("Kamu mau edit jadi apa: ");
                        scanf(" %[^\n]s", &editan_str);

                        strcpy(data_kendaraan_rumah_tangga[pos_keluarga - 1][pos_kendaraan - 1].kategori, editan_str);
                        printf("EDIT BERHASIL\n");
                    }
                    else if (input_edit == 2)
                    {
                        printf("Kamu mau edit jadi apa: ");
                        scanf(" %[^\n]s", &editan_str);

                        strcpy(data_kendaraan_rumah_tangga[pos_keluarga - 1][pos_kendaraan - 1].bahan_bakar, editan_str);
                        printf("EDIT BERHASIL\n");
                    }
                    else if (input_edit == 3)
                    {
                        printf("Kamu mau edit jadi apa: ");
                        scanf(" %[^\n]s", &editan_str);

                        strcpy(data_kendaraan_rumah_tangga[pos_keluarga - 1][pos_kendaraan - 1].nama, editan_str);
                        printf("EDIT BERHASIL\n");
                    }
                    else if (input_edit == 4)
                    {
                        printf("Kamu mau edit jadi apa: ");
                        scanf("%f", &editan_f);

                        data_kendaraan_rumah_tangga[pos_keluarga - 1][pos_kendaraan - 1].jarak_tempuh = editan_f;
                        printf("EDIT BERHASIL\n");
                    }
                    else if (input_edit == 5)
                    {
                        printf("Kamu mau edit jadi apa: ");
                        scanf("%f", &editan_f);

                        data_kendaraan_rumah_tangga[pos_keluarga - 1][pos_kendaraan - 1].konsumsi_bahan_bakar = editan_f;
                        printf("EDIT BERHASIL\n");
                    }
                    else
                    {
                        printf("Tidak ada di pilihan");
                    }

                    dihitung = belum;

                    break;

                case 4:
                    // pilihan balik ke menu sebelumnya
                    break;

                default:
                    printf("Tidak ada di pilihan");
                    break;
                }

                display_menu_input(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                scanf("%d", &input_menu);
            }
        }

        // menu analisis dan visualisasi
        else if (input_home == 2)
        {
            display_menu_analisis_visualisasi(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
            scanf("%d", &input_analisis);

            while (input_analisis != 13)
            {
                switch (input_analisis)
                {
                case 1:
                    display_menu_histogram(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_hist);

                        make_histogram(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_hist, model_mobil, size_model);

                        printf("\nKlik '1' untuk balik ke menu...\n");
                        printf("Klik '2' untuk membuat histogram lagi... ");
                        scanf("%d", &next);
                    }

                    break;

                case 2:
                    // menampilkan menu untuk sum
                    display_menu_sum(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_olah_data);

                        hitung_sum(data_kendaraan_rumah_tangga, koef_emisi, sum, jumlah_keluarga, jumlah_kendaraan, input_olah_data);
                        printf("Sum data adalah: %.2f\n\n", sum[input_olah_data - 1]);

                        printf("Klik '1' untuk balik ke menu...\n");
                        printf("Klik '2' untuk melakukan perhitungan sum lagi... ");
                        scanf("%d", &next);
                    }

                    break;

                case 3:
                    // menampilkan menu untuk standar deviasi
                    display_menu_std(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_olah_data);

                        hitung_std_deviasi(data_kendaraan_rumah_tangga, koef_emisi, sum, variansi, std_deviasi, jumlah_keluarga, jumlah_kendaraan, input_olah_data);
                        printf("Standar deviasi data adalah: %.2f\n\n", std_deviasi[input_olah_data - 1]);

                        printf("Klik '1' untuk balik ke menu...\n");
                        printf("Klik '2' untuk melakukan perhitungan standar deviasi lagi... ");
                        scanf("%d", &next);
                    }

                    break;

                case 4:
                    // menampilkan menu untuk variansi
                    display_menu_var(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_olah_data);

                        hitung_variansi(data_kendaraan_rumah_tangga, koef_emisi, sum, variansi, jumlah_keluarga, jumlah_kendaraan, input_olah_data);
                        printf("Variansi data adalah: %.2f\n\n", variansi[input_olah_data - 1]);

                        printf("Klik '1' untuk balik ke menu...\n");
                        printf("Klik '2' untuk melakukan perhitungan variansi lagi... ");
                        scanf("%d", &next);
                    }

                    break;

                case 5:
                    // menampilkan menu untuk search
                    display_menu_search(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_search);

                        if (input_search == 1 || input_search == 2 || input_search == 3)
                        {
                            printf("Tuliskan kondisi IF yang mau: (sama dengan kata apa?)\n");
                            scanf("%s", condition_kedua);

                            printf("\nKeluarga dan kendaraan yang memenuhi ketentuan tersebut adalah:\n");
                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                for (j = 0; j < jumlah_kendaraan[i]; j++)
                                {
                                    if (input_search == 1 && strncmp(data_kendaraan_rumah_tangga[i][j].kategori, condition_kedua, 20) == 0)
                                    {
                                        printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                    }
                                    else if (input_search == 2 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, condition_kedua, 20) == 0)
                                    {
                                        printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                    }
                                    else if (input_search == 3 && strncmp(data_kendaraan_rumah_tangga[i][j].nama, condition_kedua, 20) == 0)
                                    {
                                        printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                    }
                                }
                            }

                            printf("\nKlik '1' untuk balik ke menu...\n");
                            printf("Klik '2' untuk melakukan search lagi... ");
                            scanf("%d", &next);
                        }
                        else if (input_search == 4 || input_search == 5)
                        {
                            printf("Tuliskan kondisi IF yang mau: (>= / <= / < / > / ==)\n");
                            scanf("%s", condition_pertama);

                            if (strncmp(condition_pertama, ">", 5) == 0)
                            {
                                printf("Tuliskan kondisi IF yang mau: (> dari ANGKA berapa?)\n");
                                kondisi = bigger;
                            }
                            else if (strncmp(condition_pertama, "<", 5) == 0)
                            {
                                printf("Tuliskan kondisi IF yang mau: (< dari ANGKA berapa?)\n");
                                kondisi = smaller;
                            }
                            else if (strncmp(condition_pertama, "==", 5) == 0)
                            {
                                printf("Tuliskan kondisi IF yang mau: (== dari ANGKA berapa?)\n");
                                kondisi = equal;
                            }
                            else if (strncmp(condition_pertama, "<=", 5) == 0)
                            {
                                printf("Tuliskan kondisi IF yang mau: (<= dari ANGKA berapa?)\n");
                                kondisi = smaller_equal;
                            }
                            else if (strncmp(condition_pertama, ">=", 5) == 0)
                            {
                                printf("Tuliskan kondisi IF yang mau: (>= dari ANGKA berapa?)\n");
                                kondisi = bigger_equal;
                            }
                            scanf("%s", condition_kedua);

                            printf("Keluarga dan kendaraan yang memenuhi ketentuan tersebut adalah:\n");

                            if (kondisi == smaller)
                            {
                                for (i = 0; i < jumlah_keluarga; i++)
                                {
                                    for (j = 0; j < jumlah_kendaraan[i]; j++)
                                    {
                                        if (input_search == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh < atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                        else if (input_search == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar < atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                    }
                                }
                            }
                            else if (kondisi == bigger)
                            {
                                for (i = 0; i < jumlah_keluarga; i++)
                                {
                                    for (j = 0; j < jumlah_kendaraan[i]; j++)
                                    {
                                        if (input_search == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh > atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                        else if (input_search == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar > atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                    }
                                }
                            }
                            else if (kondisi == equal)
                            {
                                for (i = 0; i < jumlah_keluarga; i++)
                                {
                                    for (j = 0; j < jumlah_kendaraan[i]; j++)
                                    {
                                        if (input_search == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh == atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                        else if (input_search == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar == atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                    }
                                }
                            }
                            else if (kondisi == smaller_equal)
                            {
                                for (i = 0; i < jumlah_keluarga; i++)
                                {
                                    for (j = 0; j < jumlah_kendaraan[i]; j++)
                                    {
                                        if (input_search == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh <= atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                        else if (input_search == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar <= atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                    }
                                }
                            }
                            else if (kondisi == bigger_equal)
                            {
                                for (i = 0; i < jumlah_keluarga; i++)
                                {
                                    for (j = 0; j < jumlah_kendaraan[i]; j++)
                                    {
                                        if (input_search == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh >= atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                        else if (input_search == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar >= atoi(condition_kedua))
                                        {
                                            printf("Keluarga ke-%d, Kendaraan ke-%d\n", i + 1, j + 1);
                                        }
                                    }
                                }

                                printf("Klik '1' untuk balik ke menu...\n");
                                printf("Klik '2' untuk melakukan search lagi... ");
                                scanf("%d", &next);
                            }
                        }
                    }

                    break;

                case 6:
                    // menampilkan menu untuk min
                    display_menu_min(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_min);

                        min = min_data(data_kendaraan_rumah_tangga, koef_emisi, jumlah_keluarga, jumlah_kendaraan, input_min);
                        printf("Max data dari kolom tersebut adalah: %.2f\n\n", min);

                        printf("Klik '1' untuk balik ke menu...\n");
                        printf("Klik '2' untuk melakukan perhitungan nilai min lagi... ");
                        scanf("%d", &next);
                    }

                    break;

                case 7:
                    // menampilkan menu untuk max
                    display_menu_max(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_max);

                        max = max_data(data_kendaraan_rumah_tangga, koef_emisi, jumlah_keluarga, jumlah_kendaraan, input_max);
                        printf("Min data dari kolom tersebut adalah: %.2f\n\n", max);

                        printf("Klik '1' untuk balik ke menu...\n");
                        printf("Klik '2' untuk melakukan perhitungan nilai max lagi... ");
                        scanf("%d", &next);
                    }

                    break;

                case 8:
                    // menampilkan menu untuk count
                    display_menu_count_pertama(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;
                    printf("Pilihlah mode count mana yang ingin dipakai: ");
                    scanf("%d", &input_count);

                    if (input_count == 1)
                    {
                        display_menu_count_kedua(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);

                        while (next != 1)
                        {
                            scanf("%d", &input_count);

                            printf("Jumlah count untuk kolom tersebut adalah: %d\n\n", count_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan));

                            printf("Klik '1' untuk balik ke menu...\n");
                            printf("Klik '2' untuk melakukan perhitungan count lagi... ");
                            scanf("%d", &next);
                        }
                    }
                    else if (input_count == 2)
                    {
                        display_menu_countif(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);

                        while (next != 1)
                        {
                            scanf("%d", &input_count);

                            if (input_count == 1 || input_count == 2 || input_count == 3)
                            {
                                printf("Tuliskan kondisi IF yang mau: (sama dengan kata apa?)\n");
                                scanf("%s", condition_kedua);

                                printf("\nJumlah count untuk kolom tersebut adalah: %d\n", count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_count, condition_kedua));

                                printf("\nKlik '1' untuk balik ke menu...\n");
                                printf("Klik '2' untuk melakukan perhitungan count lagi... ");
                                scanf("%d", &next);
                            }
                            else if (input_count == 4 || input_count == 5)
                            {
                                printf("Tuliskan kondisi IF yang mau: (>= / <= / < / > / ==)\n");
                                scanf("%s", condition_pertama);

                                if (strncmp(condition_pertama, ">", 5) == 0)
                                {
                                    printf("Tuliskan kondisi IF yang mau: (> dari ANGKA berapa?)\n");
                                    kondisi = bigger;
                                }
                                else if (strncmp(condition_pertama, "<", 5) == 0)
                                {
                                    printf("Tuliskan kondisi IF yang mau: (< dari ANGKA berapa?)\n");
                                    kondisi = smaller;
                                }
                                else if (strncmp(condition_pertama, "==", 5) == 0)
                                {
                                    printf("Tuliskan kondisi IF yang mau: (== dari ANGKA berapa?)\n");
                                    kondisi = equal;
                                }
                                else if (strncmp(condition_pertama, "<=", 5) == 0)
                                {
                                    printf("Tuliskan kondisi IF yang mau: (<= dari ANGKA berapa?)\n");
                                    kondisi = smaller_equal;
                                }
                                else if (strncmp(condition_pertama, ">=", 5) == 0)
                                {
                                    printf("Tuliskan kondisi IF yang mau: (>= dari ANGKA berapa?)\n");
                                    kondisi = bigger_equal;
                                }
                                scanf("%s", condition_kedua);

                                printf("\nJumlah count untuk kolom tersebut adalah: %d\n\n", count_if_data_int(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_count, kondisi, condition_kedua));

                                printf("Klik '1' untuk balik ke menu...\n");
                                printf("Klik '2' untuk melakukan perhitungan count lagi... ");
                                scanf("%d", &next);
                            }
                        }
                    }

                    break;

                case 9:
                    display_menu_sortir(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                    next = 2;

                    while (next != 1)
                    {
                        printf("Input kolom: ");
                        scanf("%d", &input_sortir);
                        if (input_sortir == 1)
                        {
                            array_sorting co2[jumlah_keluarga];

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                co2[i].nilai = 0;
                            }

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                sprintf(co2[i].nama, "Keluarga %d", i + 1);
                                for (j = 0; j < jumlah_kendaraan[i]; j++)
                                {
                                    co2[i].nilai += data_kendaraan_rumah_tangga[i][j].jumlah_emisi[0];
                                }
                            }

                            if (dihitung == belum)
                            {
                                printf("\nJumlah emisi terkait tidak ditemukan / perlu diupdate. Harap lakukan perhitungan data emisi terlebih dahulu\n");
                            }
                            else
                            {
                                sorting(co2, jumlah_keluarga);
                                printf("Urutan keluarga dengan jejak emisi CO2 terbanyak : ");
                                for (i = jumlah_keluarga - 1; i >= 0; i--)
                                {
                                    printf("\n%s : %.2f kg", co2[i].nama, co2[i].nilai);
                                }
                                puts("");
                            }
                        }
                        else if (input_sortir == 2)
                        {
                            array_sorting n2o[jumlah_keluarga];

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                n2o[i].nilai = 0;
                            }

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                sprintf(n2o[i].nama, "Keluarga %d", i + 1);
                                for (j = 0; j < jumlah_kendaraan[i]; j++)
                                {
                                    n2o[i].nilai += data_kendaraan_rumah_tangga[i][j].jumlah_emisi[1];
                                }
                            }

                            if (dihitung == belum)
                            {
                                printf("\nJumlah emisi terkait tidak ditemukan / perlu diupdate. Harap lakukan perhitungan data emisi terlebih dahulu\n");
                            }
                            else
                            {
                                sorting(n2o, jumlah_keluarga);
                                printf("Urutan keluarga dengan jejak emisi N2O terbanyak : ");
                                for (i = jumlah_keluarga - 1; i >= 0; i--)
                                {
                                    printf("\n%s : %.2f kg", n2o[i].nama, n2o[i].nilai);
                                }
                                puts("");
                            }
                        }
                        else if (input_sortir == 3)
                        {
                            array_sorting co[jumlah_keluarga];

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                co[i].nilai = 0;
                            }

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                sprintf(co[i].nama, "Keluarga %d", i + 1);
                                for (j = 0; j < jumlah_kendaraan[i]; j++)
                                {
                                    co[i].nilai += data_kendaraan_rumah_tangga[i][j].jumlah_emisi[2];
                                }
                            }

                            if (dihitung == belum)
                            {
                                printf("\nJumlah emisi terkait tidak ditemukan / perlu diupdate. Harap lakukan perhitungan data emisi terlebih dahulu\n");
                            }
                            else
                            {
                                sorting(co, jumlah_keluarga);
                                printf("Urutan keluarga dengan jejak emisi CO terbanyak : ");
                                for (i = jumlah_keluarga - 1; i >= 0; i--)
                                {
                                    printf("\n%s : %.2f kg", co[i].nama, co[i].nilai);
                                }
                                puts("");
                            }
                        }
                        else if (input_sortir == 4)
                        {
                            array_sorting ch4[jumlah_keluarga];

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                ch4[i].nilai = 0;
                            }

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                sprintf(ch4[i].nama, "Keluarga %d", i + 1);
                                for (j = 0; j < jumlah_kendaraan[i]; j++)
                                {
                                    ch4[i].nilai += data_kendaraan_rumah_tangga[i][j].jumlah_emisi[3];
                                }
                            }

                            if (dihitung == belum)
                            {
                                printf("\nJumlah emisi terkait tidak ditemukan / perlu diupdate. Harap lakukan perhitungan data emisi terlebih dahulu\n");
                            }
                            else
                            {
                                sorting(ch4, jumlah_keluarga);
                                printf("Urutan keluarga dengan jejak emisi CH4 terbanyak : ");
                                for (i = jumlah_keluarga - 1; i >= 0; i--)
                                {
                                    printf("\n%s : %.2f kg", ch4[i].nama, ch4[i].nilai);
                                }
                                puts("");
                            }
                        }
                        else if (input_sortir == 5)
                        {
                            array_sorting total[jumlah_keluarga];

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                total[i].nilai = 0;
                            }

                            for (i = 0; i < jumlah_keluarga; i++)
                            {
                                sprintf(total[i].nama, "Keluarga %d", i + 1);
                                for (j = 0; j < jumlah_kendaraan[i]; j++)
                                {
                                    total[i].nilai += (data_kendaraan_rumah_tangga[i][j].jumlah_emisi[0] + data_kendaraan_rumah_tangga[i][j].jumlah_emisi[1] +
                                                       data_kendaraan_rumah_tangga[i][j].jumlah_emisi[2] + data_kendaraan_rumah_tangga[i][j].jumlah_emisi[3]);
                                }
                            }

                            if (total[0].nilai == 0)
                            {
                                printf("\nJumlah emisi terkait tidak ditemukan / perlu diupdate. Harap lakukan perhitungan data emisi terlebih dahulu\n");
                            }
                            else
                            {
                                sorting(total, jumlah_keluarga);
                                printf("Urutan keluarga dengan jejak emisi total terbanyak : ");
                                for (i = jumlah_keluarga - 1; i >= 0; i--)
                                {
                                    printf("\n%s : %.2f kg", total[i].nama, total[i].nilai);
                                }
                                puts("");
                            }
                        }
                        else
                        {
                            printf("\nTidak ada di pilihan\n");
                        }

                        printf("\nKlik '1' untuk balik ke menu...\n");
                        printf("Klik '2' untuk melakukan sortir lagi... ");
                        scanf("%d", &next);
                    }

                    break;

                case 10:
                    // emisi dari mobil ada dalam bentuk gas CO2, CO, N2O dan CH4
                    hitung_emisi(data_kendaraan_rumah_tangga, koef_emisi, jumlah_keluarga, jumlah_kendaraan);

                    if (jumlah_keluarga > 0)
                    {
                        printf(ANSI_COLOR_GREEN "====DATA EMISI BERHASIL DIHITUNG====\n\n" ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf(ANSI_COLOR_YELLOW "Masih belum ada data!!\n\n" ANSI_COLOR_RESET);
                        break;
                    }

                    for (i = 0; i < jumlah_keluarga; i++)
                    {
                        printf("DATA JUMLAH EMISI KELUARGA KE-%d\n", i + 1);

                        for (j = 0; j < jumlah_kendaraan[i]; j++)
                        {
                        	printf("KENDARAAN KE-%d\n", j + 1);
                            printf("CO2 = %.2f\n", data_kendaraan_rumah_tangga[i][j].jumlah_emisi[0]);
                            printf("N2O = %.2f\n", data_kendaraan_rumah_tangga[i][j].jumlah_emisi[1]);
                            printf("CO  = %.2f\n", data_kendaraan_rumah_tangga[i][j].jumlah_emisi[2]);
                            printf("CH4 = %.2f\n", data_kendaraan_rumah_tangga[i][j].jumlah_emisi[3]);
                        }

                        puts("");
                    }

                    // sudah menghitung sehingga opsi sortir sudah bisa
                    dihitung = sudah;

                    printf("Klik '1' untuk balik ke menu... ");
                    scanf("%d", &next);

                    break;

                case 11:
                    // nilai pada array diset jadi 0 dulu setiap kali dipanggil
                    for (i = 0; i < 4; i++)
                    {
                        kategori_pemborosan_mobil[i] = 0;
                    }
                    for (i = 0; i < 3; i++)
                    {
                        kategori_pemborosan_motor[i] = 0;
                    }

                    printf("Kategori Pemborosan Energi\n");

                    for (i = 0; i < jumlah_keluarga; i++)
                    {
                        for (j = 0; j < jumlah_kendaraan[i]; j++)
                        {
                            printf("\tKeluarga ke-%d, kendaraan ke-%d\n", i + 1, j + 1);

                            if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "mobil", 10) == 0)
                            {
                                if (data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar >= 0.2)
                                {
                                    printf("\t\tSANGAT BOROS\n");
                                    printf("\t\t1. Mohon mengecek kondisi mesin di bengkel karena mesinnya sudah rusak akibat sudah kelamaan dipakai\n");
                                    kategori_pemborosan_mobil[0]++;
                                }
                                else if (data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar >= 0.1 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar < 0.2)
                                {
                                    printf("\t\tBOROS\n");
                                    printf("\t\t1. Hati-hati akan efisiensi mobil yang akan terus turun / konsumsi bahan bakar yang akan terus naik ke depannya\n");
                                    kategori_pemborosan_mobil[1]++;
                                }
                                else if (data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar >= 0.05 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar < 0.1)
                                {
                                    printf("\t\tLUMAYAN TIDAK BOROS\n");
                                    printf("\t\t1. Sudah mulai hebat!!\n");
                                    printf("\t\t2. Hati-hati akan efisiensi mobil yang akan terus turun / konsumsi bahan bakar yang akan terus naik ke depannya\n");
                                    kategori_pemborosan_mobil[2]++;
                                }
                                else
                                {
                                    printf("\t\tTIDAK BOROS\n");
                                    printf("\t\t1. Selamat Anda telah mendapatkan transportasi yang menggunakan energi HANDAL dan AMAN\n");
                                    kategori_pemborosan_mobil[3]++;
                                }
                            }
                            else
                            {
                                if (data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar >= 0.05)
                                {
                                    printf("\t\tSANGAT BOROS\n");
                                    printf("\t\t1. Mohon mengecek kondisi mesin di bengkel karena mesinnya sudah rusak akibat sudah kelamaan dipakai\n");
                                    kategori_pemborosan_motor[0]++;
                                }
                                else if (data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar >= 0.02 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar < 0.05)
                                {
                                    printf("\t\tBOROS\n");
                                    printf("\t\t2. Hati-hati akan efisiensi motor yang akan terus turun ke depannya\n");
                                    kategori_pemborosan_motor[1]++;
                                }
                                else
                                {
                                    printf("\t\tTIDAK BOROS\n");
                                    printf("\t\t1. Selamat Anda telah mendapatkan transportasi yang menggunakan energi HANDAL dan AMAN\n");
                                    kategori_pemborosan_motor[2]++;
                                }
                            }
                        }
                    }

                    printf("\nMOBIL\n");
                    printf("\tSANGAT BOROS: %.2f%%\n", 100 * (float)(kategori_pemborosan_mobil[0]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "mobil"));
                    printf("\tBOROS: %.2f%%\n", 100 * (float)(kategori_pemborosan_mobil[1]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "mobil"));
                    printf("\tLUMAYAN BOROS: %.2f%%\n", 100 * (float)(kategori_pemborosan_mobil[2]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "mobil"));
                    printf("\tTIDAK BOROS: %.2f%%\n", 100 * (float)(kategori_pemborosan_mobil[3]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "mobil"));

                    printf("\nMOTOR\n");
                    printf("\tSANGAT BOROS: %.2f%%\n", 100 * (float)(kategori_pemborosan_motor[0]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "motor"));
                    printf("\tBOROS: %.2f%%\n", 100 * (float)(kategori_pemborosan_motor[1]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "motor"));
                    printf("\tTIDAK BOROS: %.2f%%\n", 100 * (float)(kategori_pemborosan_motor[2]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "motor"));

                    printf("Klik '1' untuk balik ke menu... ");
                    scanf("%d", &next);

                    break;

                case 12:
                    // membuat semua nilai pada array jadi 0 setiap kali dipanggil
                    for (i = 0; i < 2; i++)
                    {
                        kategori_sustainable_mobil[i] = 0;
                        kategori_sustainable_motor[i] = 0;
                    }

                    printf("Kategori Sustainable\n");

                    for (i = 0; i < jumlah_keluarga; i++)
                    {
                        for (j = 0; j < jumlah_kendaraan[i]; j++)
                        {
                            printf("\tKeluarga ke-%d, kendaraan ke-%d\n", i + 1, j + 1);
                            if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "mobil", 10) == 0)
                            {
                                if (strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "bensin", 10) == 0 || strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "solar", 10) == 0)
                                {
                                    printf("\t\tTIDAK SUSTAINABLE\n");
                                    printf("\t\t1. Gunakanlah bahan bakar yang lebih aman buat lingkungan seperti biodiesel atau gas alam\n");
                                    printf("\t\t2. Ganti menggunakan transportasi berbasis listrik juga sangat disarankan\n");
                                    kategori_sustainable_mobil[0]++;
                                }
                                else
                                {
                                    printf("\t\tSUSTAINABLE\n");
                                    printf("\t\t1. Selamat Anda telah mendapatkan transportasi yang menggunakan energi HANDAL dan AMAN\n");
                                    kategori_sustainable_mobil[1]++;
                                }
                            }
                            else
                            {
                                if (strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "bensin", 10) == 0)
                                {
                                    printf("\t\tTIDAK SUSTAINABLE\n");
                                    printf("\t\t1. Gunakanlah bahan bakar yang lebih aman buat lingkungan seperti biodiesel atau gas alam\n");
                                    printf("\t\t2. Ganti menggunakan transportasi berbasis listrik juga sangat disarankan\n");
                                    kategori_sustainable_motor[0]++;
                                }
                                else
                                {
                                    printf("\t\tSUSTAINABLE\n");
                                    printf("\t\t1. Selamat Anda telah mendapatkan transportasi yang menggunakan energi HANDAL dan AMAN\n");
                                    kategori_sustainable_motor[1]++;
                                }
                            }
                        }
                    }

                    printf("\nMOBIL\n");
                    printf("\tTIDAK SUSTAINABLE: %.2f\%\n", 100 * (float)(kategori_sustainable_mobil[0]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "mobil"));
                    printf("\tSUSTAINABLE: %.2f\%\n", 100 * (float)(kategori_sustainable_mobil[1]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "mobil"));

                    printf("\nMOTOR\n");
                    printf("\tTIDAK SUSTAINABLE: %.2f\%\n", 100 * (float)(kategori_sustainable_motor[0]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "motor"));
                    printf("\tSUSTAINABLE: %.2f\%\n", 100 * (float)(kategori_sustainable_motor[1]) / count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, 1, "motor"));

                    printf("Klik '1' untuk balik ke menu... ");
                    scanf("%d", &next);

                    break;

                case 13:
                    break;

                default:
                    break;
                }

                display_menu_analisis_visualisasi(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
                scanf("%d", &input_analisis);
            }
        }

        else if (input_home == 3)
        {
            // display petunjuk program
            display_petunjuk_program();
            printf("\nKlik '1' untuk balik ke menu... ");
            scanf("%d", &next);
        }

        else if (input_home == 4)
        {
            // display tentang program
            display_tentang_program();
            printf("\n\nKlik '1' untuk balik ke menu... ");
            scanf("%d", &next);
        }

        else
        {
            // error handling apabila salah input
            system("cls");
            printf("Tidak ada di pilihan... Silakan pilih lagi yang benar!!");
            printf("Klik '1' untuk balik ke menu... ");
            scanf("%d", &next);
        }

        // display menu home lagi untuk perulangan
        display_menu_home();
        scanf("%d", &input_home);
    }

    // dealokasi memori untuk array dari string
    for (i = 0; i < SIZE; i++)
    {
        free(*(model_mobil + i));
    }
    free(model_mobil);

    // dealokasi memori untuk array dari structs
    for (i = 0; i < jumlah_keluarga; i++)
    {
        free(data_kendaraan_rumah_tangga[i]);
    }
    free(data_kendaraan_rumah_tangga);

    return 0;
}

// semua function display menu
void display_sdg()
{
    // bentuk logo SDG 7
    printf(ANSI_COLOR_RED " ######  ########   ######   ########\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_GREEN "##    ## ##     ## ##    ##  ##    ##\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "##       ##     ## ##            ##  \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE " ######  ##     ## ##   ####    ##   \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "      ## ##     ## ##    ##    ##    \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "##    ## ##     ## ##    ##    ##    \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_RED " ######  ########   ######     ##    \n" ANSI_COLOR_RESET);
}

void display_data(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    int i, j;
    for (i = 0; i < jumlah_keluarga; i++)
    {
        printf("KELUARGA KE-%d\n", i + 1);
        for (j = 0; j < jumlah_kendaraan[i]; j++)
        {
            printf("\tKENDARAAN KE-%d\n", j + 1);
            printf("\tKategori\t\t: %s\n", data_kendaraan_rumah_tangga[i][j].kategori);
            printf("\tBahan bakar\t\t: %s\n", data_kendaraan_rumah_tangga[i][j].bahan_bakar);
            printf("\tNama model\t\t: %s\n", data_kendaraan_rumah_tangga[i][j].nama);
            printf("\tJarak tempuh\t\t: %.2f km\n", data_kendaraan_rumah_tangga[i][j].jarak_tempuh);
            printf("\tKonsumsi bahan bakar\t: %.2f L/km\n", data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar);
        }
    }
}

void display_petunjuk_program()
{
    system("cls");
    printf(".####.##....##..######..########.########..##.....##..######..########.####..#######..##....##..######.\n");
    printf("..##..###...##.##....##....##....##.....##.##.....##.##....##....##.....##..##.....##.###...##.##....##\n");
    printf("..##..####..##.##..........##....##.....##.##.....##.##..........##.....##..##.....##.####..##.##......\n");
    printf("..##..##.##.##..######.....##....########..##.....##.##..........##.....##..##.....##.##.##.##..######.\n");
    printf("..##..##..####.......##....##....##...##...##.....##.##..........##.....##..##.....##.##..####.......##\n");
    printf("..##..##...###.##....##....##....##....##..##.....##.##....##....##.....##..##.....##.##...###.##....##\n");
    printf(".####.##....##..######.....##....##.....##..#######...######.....##....####..#######..##....##..######.\n");
    printf("\nTerdapat tiga menu utama dalam program ini, yakni menu utama, menu input, dan menu visualisasi. Di dalam menu utama, tersedia pilihan untuk navigasi ke menu input dan menu visualisasi, opsi untuk memperoleh petunjuk dan informasi umum mengenai program, serta keluar dari program. Pada menu input, terdapat opsi untuk menambahkan data, mengedit data, dan mengurangi data. Sementara itu, di dalam menu visualisasi, terdapat opsi untuk menjalankan berbagai fungsi analisis dan visualisasi.\n");
    printf("\nFitur Input:\n");
    printf("   1. Tambahkan data\n");
    printf("   2. Kurangi data\n");
    printf("   3. Edit data\n");
    printf("   4. Balik ke menu sebelumnya\n");
    printf("\nFitur Analisis & Visualisasi:\n");
    printf("   1.  Tampilkan histogram\n");
    printf("   2.  Tampilkan sum dari kolom [...]\n");
    printf("   3.  Tampilkan standar deviasi dari kolom [...]\n");
    printf("   4.  Tampilkan variansi dari kolom [...]\n");
    printf("   5.  Tampilkan index dari data [...]\n");
    printf("   6.  Tampilkan min dari data [...]\n");
    printf("   7.  Tampilkan max dari data [...]\n");
    printf("   8.  Tampilkan count dari data [...]\n");
    printf("   9.  Sortir data berdasarkan kolom [...]\n");
    printf("   10. Hitung data emisi\n");
    printf("   11. Tampilkan kategori pemborosan energi\n");
    printf("   12. Tampilkan kategori sustainable\n");
    printf("   13. Balik ke menu sebelumnya\n");
}

void display_tentang_program()
{
    system("cls");
    display_sdg();
    printf("\nSDG 7 dibuat karena menyadari bahwa banyak orang masih tidak memiliki akses ke energi yang sustainable. Tanpa energi yang sustainable, lingkungan dapat rusak dan berdampak negatif pada kehidupan. Program ini difokuskan pada sektor transportasi dari SDG 7, dengan tujuan mendorong Target 7.1, yaitu 'Pada 2030, pastikan akses universal terhadap layanan energi yang terjangkau, handal, dan modern' dan juga target 7.b, yaitu 'Pada 2030, perluas infrastruktur dan tingkatkan teknologi untuk menyediakan layanan energi modern dan sustainable untuk semua di negara-negara berkembang, khususnya negara-negara yang paling kurang berkembang, negara-negara kepulauan kecil, dan negara-negara berkembang yang terkurung daratan, sesuai dengan program dukungan masing-masing.'\n");
    printf("\nTransportasi sustainable mengacu pada moda transportasi yang ramah lingkungan, hemat energi, dan terjangkau, termasuk kendaraan listrik dan bahan bakar alternatif, serta bahan bakar domestik. Manfaat transportasi sustainable meliputi penghematan biaya bahan bakar dan kendaraan, serta pengurangan emisi karbon dari pembakaran bahan bakar fosil, yang mengakibatkan polusi udara yang lebih rendah. Oleh karena itu, program ini dirancang untuk mencapai tujuan tersebut.\n");
    printf("\nPertama, ada sebuah menu yang berisi berbagai opsi untuk memasukkan data atau hasil perhitungan dari data yang ada. Sistem database kemudian akan menerima input tentang penggunaan alat transportasi (motor dan mobil) dari berbagai rumah tangga, seperti jumlah kendaraan dan konsumsi bahan bakar, dll.\n");
    printf("\nSelanjutnya, output akan menampilkan berbagai parameter sebagai indikator seberapa sustainable rumah tangga dalam hal transportasi. Ini dapat ditampilkan melalui kategori tingkat keberlanjutan rumah tangga, kontribusi terhadap pemborosan energi, dan sebagainya.");
}

void display_menu_home()
{
    // bentuk menu home
    system("cls");
    printf("============================================================================\n");
    printf("|                                Menu Home                                 |\n");
    printf("============================================================================\n");
    printf("| 1. Input data                                                            |\n");
    printf("| 2. Analisis dan visualisasi data                                         |\n");
    printf("| 3. Petunjuk program                                                      |\n");
    printf("| 4. Tentang program                                                       |\n");
    printf("| 5. Exit program                                                          |\n");
    printf("============================================================================\n");
}

void display_menu_input(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                                Menu Input                                |\n");
    printf("============================================================================\n");
    printf("| 1. Tambahkan data                                                        |\n");
    printf("| 2. Kurangi data                                                          |\n");
    printf("| 3. Edit data                                                             |\n");
    printf("| 4. Balik ke menu sebelumnya                                              |\n");
    printf("============================================================================\n");
}

void display_menu_analisis_visualisasi(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                        Menu Analisis & Visualisasi                       |\n");
    printf("============================================================================\n");
    printf("| 1.  Tampilkan histogram                                                  |\n");
    printf("| 2.  Tampilkan sum dari kolom [...]                                       |\n");
    printf("| 3.  Tampilkan standar deviasi dari kolom [...]                           |\n");
    printf("| 4.  Tampilkan variansi dari kolom [...]                                  |\n");
    printf("| 5.  Tampilkan index dari data [...]                                      |\n");
    printf("| 6.  Tampilkan min dari data [...]                                        |\n");
    printf("| 7.  Tampilkan max dari data [...]                                        |\n");
    printf("| 8.  Tampilkan count dari data [...]                                      |\n");
    printf("| 9.  Sortir data berdasarkan kolom [...]                                  |\n");
    printf("| 10. Hitung data emisi                                                    |\n");
    printf("| 11. Tampilkan kategori pemborosan energi                                 |\n");
    printf("| 12. Tampilkan kategori sustainable                                       |\n");
    printf("| 13. Balik ke menu sebelumnya                                             |\n");
    printf("============================================================================\n");
}

void display_menu_sum(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                                Menu Sum                                  |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dicari sum:                                    |\n");
    printf("| 1. Jarak tempuh                                                          |\n");
    printf("| 2. Konsumsi bahan bakar                                                  |\n");
    printf("| 3. Jumlah emisi CO2                                                      |\n");
    printf("| 4. Jumlah emisi CO                                                       |\n");
    printf("| 5. Jumlah emisi N2O                                                      |\n");
    printf("| 6. Jumlah emisi CH4                                                      |\n");
    printf("============================================================================\n");
}

void display_menu_search(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                               Menu Search                                |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin di-search:                                     |\n");
    printf("| 1. Kategori                                                              |\n");
    printf("| 2. Bahan Bakar                                                           |\n");
    printf("| 3. Nama model                                                            |\n");
    printf("| 4. Jarak tempuh                                                          |\n");
    printf("| 5. Konsumsi bahan bakar                                                  |\n");
    printf("============================================================================\n");
}

void display_menu_min(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                                 Menu Min                                 |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dicari minimal:                                |\n");
    printf("| 1. Jarak tempuh                                                          |\n");
    printf("| 2. Konsumsi bahan bakar                                                  |\n");
    printf("| 3. Jumlah emisi CO2                                                      |\n");
    printf("| 4. Jumlah emisi CO                                                       |\n");
    printf("| 5. Jumlah emisi N2O                                                      |\n");
    printf("| 6. Jumlah emisi CH4                                                      |\n");
    printf("============================================================================\n");
}

void display_menu_max(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                                 Menu Max                                 |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dicari maksimal:                               |\n");
    printf("| 1. Jarak tempuh                                                          |\n");
    printf("| 2. Konsumsi bahan bakar                                                  |\n");
    printf("| 3. Jumlah emisi CO2                                                      |\n");
    printf("| 4. Jumlah emisi CO                                                       |\n");
    printf("| 5. Jumlah emisi N2O                                                      |\n");
    printf("| 6. Jumlah emisi CH4                                                      |\n");
    printf("============================================================================\n");
}

void display_menu_var(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                              Menu Variansi                               |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dicari variansi:                               |\n");
    printf("| 1. Jarak tempuh                                                          |\n");
    printf("| 2. Konsumsi bahan bakar                                                  |\n");
    printf("| 3. Jumlah emisi CO2                                                      |\n");
    printf("| 4. Jumlah emisi CO                                                       |\n");
    printf("| 5. Jumlah emisi N2O                                                      |\n");
    printf("| 6. Jumlah emisi CH4                                                      |\n");
    printf("============================================================================\n");
}

void display_menu_std(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                           Menu Standar Deviasi                           |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dicari standar deviasi:                        |\n");
    printf("| 1. Jarak tempuh                                                          |\n");
    printf("| 2. Konsumsi bahan bakar                                                  |\n");
    printf("| 3. Jumlah emisi CO2                                                      |\n");
    printf("| 4. Jumlah emisi CO                                                       |\n");
    printf("| 5. Jumlah emisi N2O                                                      |\n");
    printf("| 6. Jumlah emisi CH4                                                      |\n");
    printf("============================================================================\n");
}

void display_menu_edit(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                                Menu Edit                                 |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin diedit:                                        |\n");
    printf("| 1. Kategori                                                              |\n");
    printf("| 2. Bahan Bakar                                                           |\n");
    printf("| 3. Nama model                                                            |\n");
    printf("| 4. Jarak tempuh                                                          |\n");
    printf("| 5. Konsumsi bahan bakar                                                  |\n");
    printf("============================================================================\n");
}

void display_menu_histogram(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                               Menu Histogram                             |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dibikin histogram:                             |\n");
    printf("| 1. Kategori                                                              |\n");
    printf("| 2. Bahan bakar                                                           |\n");
    printf("| 3. Nama model                                                            |\n");
    printf("============================================================================\n");
}

void display_menu_count_pertama(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                             Menu Count #1                                |\n");
    printf("============================================================================\n");
    printf("| 1. Pilih kolom tanpa IF                                                  |\n");
    printf("| 2. Pilih kolom dengan IF                                                 |\n");
    printf("============================================================================\n");
}

void display_menu_count_kedua(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                             Menu Count #2                                |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dicari count:                                  |\n");
    printf("| 1. Kategori                                                              |\n");
    printf("| 2. Bahan Bakar                                                           |\n");
    printf("| 3. Nama model                                                            |\n");
    printf("| 4. Jarak tempuh                                                          |\n");
    printf("| 5. Konsumsi bahan bakar                                                  |\n");
    printf("============================================================================\n");
}

void display_menu_countif(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                              Menu CountIF                                |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin dicari count:                                  |\n");
    printf("| 1. Kategori                                                              |\n");
    printf("| 2. Bahan Bakar                                                           |\n");
    printf("| 3. Nama model                                                            |\n");
    printf("| 4. Jarak tempuh                                                          |\n");
    printf("| 5. Konsumsi bahan bakar                                                  |\n");
    printf("============================================================================\n");
}

void display_menu_sortir(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    system("cls");
    display_data(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan);
    printf("============================================================================\n");
    printf("|                                Menu Sortir                               |\n");
    printf("============================================================================\n");
    printf("| Pilihlah kolom yang ingin disortir:                                      |\n");
    printf("| 1. Jumlah emisi CO2                                                      |\n");
    printf("| 2. Jumlah emisi CO                                                       |\n");
    printf("| 3. Jumlah emisi N2O                                                      |\n");
    printf("| 4. Jumlah emisi CH4                                                      |\n");
    printf("| 5. Total emisi                                                      	   |\n");
    printf("============================================================================\n");
}

// list semua function untuk aritmatika, sorting, dll
float max_data(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], int jumlah_keluarga, int jumlah_kendaraan[], int input_max)
{
    float max = 0;
    int i, j;

    if (input_max == 1)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (max < data_kendaraan_rumah_tangga[i][j].jarak_tempuh)
                {
                    max = data_kendaraan_rumah_tangga[i][j].jarak_tempuh;
                }
            }
        }
    }
    else if (input_max == 2)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (max < data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar)
                {
                    max = data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar;
                }
            }
        }
    }
    else if (input_max == 3 || input_max == 4 || input_max == 5 || input_max == 6)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                hitung_emisi(data_kendaraan_rumah_tangga, koef_emisi, jumlah_keluarga, jumlah_kendaraan);
                if (max < data_kendaraan_rumah_tangga[i][j].jumlah_emisi[input_max - 3])
                {
                    max = data_kendaraan_rumah_tangga[i][j].jumlah_emisi[input_max - 3];
                }
            }
        }
    }

    return max;
}

void hitung_emisi(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], int jumlah_keluarga, int jumlah_kendaraan[])
{
    int i, j, k;

    for (i = 0; i < jumlah_keluarga; i++)
    {
        for (j = 0; j < jumlah_kendaraan[i]; j++)
        {
            if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "mobil", 5) == 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "bensin", 6) == 0)
            {
                for (k = 0; k < 4; k++)
                {
                    data_kendaraan_rumah_tangga[i][j].jumlah_emisi[k] = data_kendaraan_rumah_tangga[i][j].jarak_tempuh * data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar * koef_emisi[0][k];
                }
            }
            else if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "mobil", 5) == 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "solar", 5) == 0)
            {
                for (k = 0; k < 4; k++)
                {
                    data_kendaraan_rumah_tangga[i][j].jumlah_emisi[k] = data_kendaraan_rumah_tangga[i][j].jarak_tempuh * data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar * koef_emisi[2][k];
                }
            }
            else if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "mobil", 5) == 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "elektrik", 10) == 0)
            {
                for (k = 0; k < 4; k++)
                {
                    data_kendaraan_rumah_tangga[i][j].jumlah_emisi[k] = 0;
                }
            }
            else if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "motor", 5) == 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "bensin", 6) == 0)
            {
                for (k = 0; k < 4; k++)
                {
                    data_kendaraan_rumah_tangga[i][j].jumlah_emisi[k] = data_kendaraan_rumah_tangga[i][j].jarak_tempuh * data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar * koef_emisi[1][k];
                }
            }
            else if (strncmp(data_kendaraan_rumah_tangga[i][j].kategori, "motor", 5) == 0 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, "elektrik", 10) == 0)
            {
                for (k = 0; k < 4; k++)
                {
                    data_kendaraan_rumah_tangga[i][j].jumlah_emisi[k] = 0;
                }
            }
        }
    }
}

void hitung_sum(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], float sum[], int jumlah_keluarga, int jumlah_kendaraan[], int input_olah_data)
{
    int i, j;
    sum[input_olah_data - 1] = 0;

    if (input_olah_data == 1)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                sum[input_olah_data - 1] += data_kendaraan_rumah_tangga[i][j].jarak_tempuh;
            }
        }
    }
    else if (input_olah_data == 2)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                sum[input_olah_data - 1] += data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar;
            }
        }
    }
    else if (input_olah_data == 3 || input_olah_data == 4 || input_olah_data == 5 || input_olah_data == 6)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                hitung_emisi(data_kendaraan_rumah_tangga, koef_emisi, jumlah_keluarga, jumlah_kendaraan);
                sum[input_olah_data - 1] += data_kendaraan_rumah_tangga[i][j].jumlah_emisi[input_olah_data - 3];
            }
        }
    }
}

void hitung_variansi(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], float sum[], float variansi[], int jumlah_keluarga, int jumlah_kendaraan[], int input_olah_data)
{
    int total_kendaraan = 0, i, j;
    float sigma = 0;

    for (i = 0; i < jumlah_keluarga; i++)
    {
        for (j = 0; j < jumlah_kendaraan[i]; j++)
        {
            total_kendaraan++;
        }
    }

    hitung_sum(data_kendaraan_rumah_tangga, koef_emisi, sum, jumlah_keluarga, jumlah_kendaraan, input_olah_data);
    float rata_rata = sum[input_olah_data - 1] / total_kendaraan;

    if (input_olah_data == 1)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                sigma += pow(data_kendaraan_rumah_tangga[i][j].jarak_tempuh - rata_rata, 2);
            }
        }
    }
    else if (input_olah_data == 2)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                sigma += pow(data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar - rata_rata, 2);
            }
        }
    }
    else if (input_olah_data == 3 || input_olah_data == 4 || input_olah_data == 5 || input_olah_data == 6)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                hitung_emisi(data_kendaraan_rumah_tangga, koef_emisi, jumlah_keluarga, jumlah_kendaraan);
                sigma += pow(data_kendaraan_rumah_tangga[i][j].jumlah_emisi[input_olah_data - 3] - rata_rata, 2);
            }
        }
    }

    variansi[input_olah_data - 1] = sigma / (float)(total_kendaraan - 1);
}

void hitung_std_deviasi(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], float sum[], float variansi[], float std_deviasi[], int jumlah_keluarga, int jumlah_kendaraan[], int input_olah_data)
{
    hitung_sum(data_kendaraan_rumah_tangga, koef_emisi, sum, jumlah_keluarga, jumlah_kendaraan, input_olah_data);
    hitung_variansi(data_kendaraan_rumah_tangga, koef_emisi, sum, variansi, jumlah_keluarga, jumlah_kendaraan, input_olah_data);

    std_deviasi[input_olah_data - 1] = sqrt(variansi[input_olah_data - 1]);
}

int count_data(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[])
{
    int count = 0, i, j;

    for (i = 0; i < jumlah_keluarga; i++)
    {
        for (j = 0; j < jumlah_kendaraan[i]; j++)
        {
            count += 1;
        }
    }

    return count;
}

// function buat hitung count apabila datanya dalam tipe string
int count_if_data_str(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[], int input_count, char str_condition[])
{
    int count = 0, i, j;

    for (i = 0; i < jumlah_keluarga; i++)
    {
        for (j = 0; j < jumlah_kendaraan[i]; j++)
        {
            if (input_count == 1 && strncmp(data_kendaraan_rumah_tangga[i][j].kategori, str_condition, 20) == 0)
            {
                count += 1;
            }
            if (input_count == 2 && strncmp(data_kendaraan_rumah_tangga[i][j].bahan_bakar, str_condition, 20) == 0)
            {
                count += 1;
            }
            if (input_count == 3 && strncmp(data_kendaraan_rumah_tangga[i][j].nama, str_condition, 20) == 0)
            {
                count += 1;
            }
        }
    }

    return count;
}

// function buat hitung count apabila datanya dalam tipe integer
int count_if_data_int(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[], int input_count, conditions kondisi, char str_condition[])
{
    int count = 0, i, j;

    int num_condition = atoi(str_condition);

    if (kondisi == smaller)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (input_count == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh < num_condition)
                {
                    count += 1;
                }
                else if (input_count == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar < num_condition)
                {
                    count += 1;
                }
            }
        }
    }
    else if (kondisi == bigger)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (input_count == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh > num_condition)
                {
                    count += 1;
                }
                else if (input_count == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar > num_condition)
                {
                    count += 1;
                }
            }
        }
    }
    else if (kondisi == equal)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (input_count == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh == num_condition)
                {
                    count += 1;
                }
                else if (input_count == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar == num_condition)
                {
                    count += 1;
                }
            }
        }
    }
    else if (kondisi == smaller_equal)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (input_count == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh <= num_condition)
                {
                    count += 1;
                }
                else if (input_count == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar <= num_condition)
                {
                    count += 1;
                }
            }
        }
    }
    else if (kondisi == bigger_equal)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (input_count == 4 && data_kendaraan_rumah_tangga[i][j].jarak_tempuh >= num_condition)
                {
                    count += 1;
                }
                else if (input_count == 5 && data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar >= num_condition)
                {
                    count += 1;
                }
            }
        }
    }

    return count;
}

void sorting(array_sorting array[], int jumlah_keluarga)
{
    int i, j;
    array_sorting temp;

    for (i = 0; i < jumlah_keluarga - 1; i++)
    {
        for (j = 0; j < jumlah_keluarga - i - 1; j++)
        {
            if (array[j].nilai > array[j + 1].nilai)
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void make_histogram(kendaraan **data_kendaraan_rumah_tangga, int jumlah_keluarga, int jumlah_kendaraan[], int input_hist, char **model_mobil, int size_model)
{
    int count_bensin, count_solar, count_elektrik, count_motor, count_mobil, count_model[size_model], i, j;

    if (input_hist == 1)
    {
        count_mobil = count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_hist, "mobil");
        count_motor = count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_hist, "motor");

        printf("mobil\t");
        for (i = 0; i < count_mobil; i++)
        {
            printf("#");
        }
        puts("");

        printf("motor\t");
        for (i = 0; i < count_motor; i++)
        {
            printf("#");
        }
        puts("");
    }
    else if (input_hist == 2)
    {
        count_bensin = count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_hist, "bensin");
        count_solar = count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_hist, "solar");
        count_elektrik = count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_hist, "elektrik");

        printf("bensin\t\t");
        for (i = 0; i < count_bensin; i++)
        {
            printf("#");
        }
        puts("");

        printf("solar\t\t");
        for (i = 0; i < count_solar; i++)
        {
            printf("#");
        }
        puts("");

        printf("elektrik\t");
        for (i = 0; i < count_elektrik; i++)
        {
            printf("#");
        }
        puts("");
    }
    else if (input_hist == 3)
    {
        for (i = 0; i < size_model; i++)
        {
            count_model[i] = count_if_data_str(data_kendaraan_rumah_tangga, jumlah_keluarga, jumlah_kendaraan, input_hist, model_mobil[i]);

            printf("%s\t", model_mobil[i]);
            for (j = 0; j < count_model[i]; j++)
            {
                printf("#");
            }
            puts("");
        }
    }
}

char *to_lower(char *s)
{
    char *p;

    for (p = s; *p; p++)
    {
        *p = tolower(*p);
    }

    return s;
}

int adalah_angka(char *s)
{
    while (*s)
    {
        if (isdigit(*s))
        {
            s++;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int is_repeated(char **s, char new[])
{
    int i, repeated = 0;

    for (i = 0; i < SIZE; i++)
    {
        if (strncmp(new, s[i], 20) == 0)
        {
            repeated = 1;
        }
    }
    return repeated;
}

float min_data(kendaraan **data_kendaraan_rumah_tangga, float koef_emisi[3][4], int jumlah_keluarga, int jumlah_kendaraan[], int input_min)
{
    float min = 0;
    int i, j;

    if (input_min == 1)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (min < data_kendaraan_rumah_tangga[i][j].jarak_tempuh)
                {
                    min = data_kendaraan_rumah_tangga[i][j].jarak_tempuh;
                }
            }
        }
    }
    else if (input_min == 2)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                if (min < data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar)
                {
                    min = data_kendaraan_rumah_tangga[i][j].konsumsi_bahan_bakar;
                }
            }
        }
    }
    else if (input_min == 3 || input_min == 4 || input_min == 5 || input_min == 6)
    {
        for (i = 0; i < jumlah_keluarga; i++)
        {
            for (j = 0; j < jumlah_kendaraan[i]; j++)
            {
                hitung_emisi(data_kendaraan_rumah_tangga, koef_emisi, jumlah_keluarga, jumlah_kendaraan);
                if (min < data_kendaraan_rumah_tangga[i][j].jumlah_emisi[input_min - 3])
                {
                    min = data_kendaraan_rumah_tangga[i][j].jumlah_emisi[input_min - 3];
                }
            }
        }
    }

    return min;
}
