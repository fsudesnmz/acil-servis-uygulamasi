#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 5

// Hasta yap�s�
typedef struct {
    char name[50];
    char surname[50];
    int age;
    char tc_no[12]; // TC kimlik numaras�
    char triaj[10]; // Triaj durumu: k�rm�z�, sar�, ye�il
    char complaint[100]; // Hasta �ikayeti
    char doctor[50]; // Y�nlendirilen doktor
    char diagnosis[100]; // Te�his (doktor taraf�ndan girilir)
    char medication[100]; // �la� (doktor taraf�ndan girilir)
    char hl7_record[500]; // HL7 format�nda hasta kayd�
    int prescription_no; // Re�ete numaras�
} Patient;

// Kuyruk yap�s�
typedef struct {
    Patient patients[MAX_PATIENTS];
    int front, rear;
} Queue;

// Doktor yap�s�
typedef struct {
    char name[50];
    char specialty[50]; // Uzmanl�k alan�
} Doctor;

// Kuyruk ba�latma
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

// Kuyruk bo� mu kontrol�
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Kuyruk dolu mu kontrol�
int isFull(Queue* q) {
    return (q->rear + 1) % MAX_PATIENTS == q->front;
}

// Kuyru�a hasta ekleme
void enqueue(Queue* q, Patient p) {
    if (isFull(q)) {
        printf("Kuyruk dolu! Hasta eklenemiyor.\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_PATIENTS;
    }
    q->patients[q->rear] = p;
}

// Kuyruktan hasta ��karma
Patient dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Kuyruk bos! Hasta c�karilamiyor.\n");
        Patient emptyPatient = {"", "", 0, "", "", "", "", "", "", "", 0};
        return emptyPatient;
    }
    Patient p = q->patients[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_PATIENTS;
    }
    return p;
}

// Kuyruktaki hastalar� listeleme
void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Kuyruk bos.\n");
        return;
    }
    int i = q->front;
    while (i != q->rear) {
        printPatient(q->patients[i]);
        i = (i + 1) % MAX_PATIENTS;
    }
    printPatient(q->patients[q->rear]);
}

// Kuyruktan hasta silme (TC kimlik numaras�na g�re)
void deletePatient(Queue* q, const char* tc_no) {
    if (isEmpty(q)) {
        printf("Kuyruk bos! Silinecek hasta yok.\n");
        return;
    }
    int i = q->front;
    int found = 0;
    while (i != q->rear) {
        if (strcmp(q->patients[i].tc_no, tc_no) == 0) {
            found = 1;
            break;
        }
        i = (i + 1) % MAX_PATIENTS;
    }
    if (strcmp(q->patients[q->rear].tc_no, tc_no) == 0) {
        found = 1;
        i = q->rear;
    }
    if (found) {
        printf("Hasta bulundu ve siliniyor:\n");
        printPatient(q->patients[i]);
        if (q->front == q->rear) {
            q->front = q->rear = -1;
        } else {
            for (int j = i; j != q->rear; j = (j + 1) % MAX_PATIENTS) {
                q->patients[j] = q->patients[(j + 1) % MAX_PATIENTS];
            }
            q->rear = (q->rear - 1 + MAX_PATIENTS) % MAX_PATIENTS;
        }
        printf("Hasta basariyla silindi.\n");
    } else {
        printf("TC kimlik numarasi ile eslesen hasta bulunamadi.\n");
    }
}

// Belirli bir hastay� g�r�nt�leme (TC kimlik numaras�na g�re)
void viewPatient(Queue* q, const char* tc_no) {
    if (isEmpty(q)) {
        printf("Kuyruk bos! Goruntulenecek hasta yok.\n");
        return;
    }
    int i = q->front;
    int found = 0;
    while (i != q->rear) {
        if (strcmp(q->patients[i].tc_no, tc_no) == 0) {
            found = 1;
            break;
        }
        i = (i + 1) % MAX_PATIENTS;
    }
    if (strcmp(q->patients[q->rear].tc_no, tc_no) == 0) {
        found = 1;
        i = q->rear;
    }
    if (found) {
        printf("Hasta bulundu:\n");
        printPatient(q->patients[i]);
    } else {
        printf("TC kimlik numarasi ile eslesen hasta bulunamad�.\n");
    }
}

// Doktorlar� ba�latma
void initDoctors(Doctor doctors[], int size) {
    strcpy(doctors[0].name, "Dr. Ahmet Yilmaz");
    strcpy(doctors[0].specialty, "Kardiyoloji");

    strcpy(doctors[1].name, "Dr. Mehmet Kaya");
    strcpy(doctors[1].specialty, "N�roloji");

    strcpy(doctors[2].name, "Dr. Ayse Demir");
    strcpy(doctors[2].specialty, "Genel Cerrahi");

    strcpy(doctors[3].name, "Dr. Fatma Sahin");
    strcpy(doctors[3].specialty, "Ortopedi");

    strcpy(doctors[4].name, "Dr. Ali Veli");
    strcpy(doctors[4].specialty, "Dahiliye");
}

// Hasta �ikayetine g�re uygun doktoru bulma
char* findDoctor(Doctor doctors[], int size, const char* complaint) {
    if (strstr(complaint, "kalp") != NULL || strstr(complaint, "g���s") != NULL) {
        return doctors[0].name; // Kardiyoloji
    } else if (strstr(complaint, "ba� a�r�s�") != NULL || strstr(complaint, "sinir") != NULL) {
        return doctors[1].name; // N�roloji
    } else if (strstr(complaint, "ameliyat") != NULL || strstr(complaint, "yaralanma") != NULL) {
        return doctors[2].name; // Genel Cerrahi
    } else if (strstr(complaint, "kemik") != NULL || strstr(complaint, "eklem") != NULL) {
        return doctors[3].name; // Ortopedi
    } else if (strstr(complaint, "�ks�r�k") != NULL || strstr(complaint, "ate�") != NULL || strstr(complaint, "kusma") != NULL) {
        return doctors[4].name; // Dahiliye
    } else {
        return doctors[4].name; // Dahiliye (varsay�lan)
    }
}

// HL7 format�nda hasta kayd� olu�turma
void createHL7Record(Patient* p) {
    sprintf(p->hl7_record, "MSH|^~\\&|HOSPITAL|ER|LAB|202310101200||ADT^A01|123456|P|2.5\n"
                           "PID|||%s^%s||%d|||%s\n"
                           "PV1|||%s||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
                           "DG1|||%s\n"
                           "RXA|||%s\n"
                           "PRB|||%d", p->name, p->surname, p->age, p->tc_no, p->doctor, p->diagnosis, p->medication, p->prescription_no);
}

// Re�ete numaras� �retme
int generatePrescriptionNo() {
    return rand() % 1000000;
}

// Hasta bilgilerini ekrana yazd�rma
void printPatient(Patient p) {
    printf("Hasta Adi: %s %s\n", p.name, p.surname);
    printf("Yas: %d\n", p.age);
    printf("TC Kimlik No: %s\n", p.tc_no);
    printf("Triaj Durumu: %s\n", p.triaj);
    printf("�ikayet: %s\n", p.complaint);
    printf("Yonlendirilen Doktor: %s\n", p.doctor);
    printf("Teshis: %s\n", p.diagnosis);
    printf("Ilac: %s\n", p.medication);
    printf("Re�ete No: %d\n", p.prescription_no);
    printf("HL7 Kayd�:\n%s\n", p.hl7_record);
    printf("--------------------------\n");
}

// Yeni hasta ekleme
void addPatient(Queue* q, Doctor doctors[], int size) {
    Patient p;
    printf("Hasta Adi: ");
    scanf("%s", p.name);
    printf("Hasta Soyadi: ");
    scanf("%s", p.surname);
    printf("Yas: ");
    scanf("%d", &p.age);
    printf("TC Kimlik No: ");
    scanf("%s", p.tc_no);
    printf("Triaj Durumu (kirmizi/sari/yesil): ");
    scanf("%s", p.triaj);
    printf("Hasta Sikayeti (Oksuruk, ates, kusma, vs.): ");
    scanf(" %[^\n]", p.complaint); // Bo�luklu girdi almak i�in
    strcpy(p.doctor, findDoctor(doctors, size, p.complaint)); // Uygun doktoru bul ve kopyala
    p.prescription_no = generatePrescriptionNo(); // Re�ete numaras� �ret
    fillDoctorInfo(&p); // Doktor bilgilerini otomatik doldur
    enqueue(q, p); // Kuyru�a hasta ekle
    printf("Hasta basariyla eklendi ve %s doktoruna yonlendirildi.\n", p.doctor);
}

// Doktor bilgilerini otomatik doldurma (sistem taraf�ndan)
void fillDoctorInfo(Patient* p) {
    if (strstr(p->complaint, "kalp") != NULL || strstr(p->complaint, "g���s") != NULL) {
        strcpy(p->diagnosis, "Kalp krizi riski");
        strcpy(p->medication, "Aspirin 100 mg");
    } else if (strstr(p->complaint, "ba� a�r�s�") != NULL || strstr(p->complaint, "sinir") != NULL) {
        strcpy(p->diagnosis, "Migren");
        strcpy(p->medication, "Parol 500 mg");
    } else if (strstr(p->complaint, "ameliyat") != NULL || strstr(p->complaint, "yaralanma") != NULL) {
        strcpy(p->diagnosis, "Cerrahi m�dahale gerekiyor");
        strcpy(p->medication, "Agri kesici");
    } else if (strstr(p->complaint, "kemik") != NULL || strstr(p->complaint, "eklem") != NULL) {
        strcpy(p->diagnosis, "K�r�k veya ��k�k");
        strcpy(p->medication, "Alc� ve agr� kesici");
    } else if (strstr(p->complaint, "�ks�r�k") != NULL || strstr(p->complaint, "ate�") != NULL || strstr(p->complaint, "kusma") != NULL) {
        strcpy(p->diagnosis, "Grip veya enfeksiyon");
        strcpy(p->medication, "Antibiyotik ve ates dusurucu");
    } else {
        strcpy(p->diagnosis, "Genel muayene gerekiyor");
        strcpy(p->medication, "Vitamin takviyesi");
    }
    createHL7Record(p); // HL7 kayd�n� g�ncelle
}

int main() {
    Queue q;
    initQueue(&q);

    Doctor doctors[MAX_DOCTORS];
    initDoctors(doctors, MAX_DOCTORS);

    srand(time(NULL)); // Rastgele re�ete numaras� �retmek i�in

    int choice;
    do {
        printf("\nAcil Servis Uygulamasi\n");
        printf("1. Yeni Hasta Ekle\n");
        printf("2. Hasta Bilgileri Goruntule\n");
        printf("3. Eklenen Tum Hastalari Goruntule\n");
        printf("4. Hasta Sil\n");
        printf("5. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                addPatient(&q, doctors, MAX_DOCTORS);
                break;
            }
            case 2: {
                char tc_no[12];
                printf("Goruntulenecek hastanin TC kimlik numarasini girin: ");
                scanf("%s", tc_no);
                viewPatient(&q, tc_no);
                break;
            }
            case 3: {
                printf("\nEklenen Tum Hastalar:\n");
                printQueue(&q);
                break;
            }
            case 4: {
                char tc_no[12];
                printf("Silinecek hastanin TC kimlik numarasini girin: ");
                scanf("%s", tc_no);
                deletePatient(&q, tc_no);
                break;
            }
            case 5: {
                printf("Cikis yapiliyor...\n");
                break;
            }
            default: {
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
                break;
            }
        }
    } while (choice != 5);

    return 0;
}
