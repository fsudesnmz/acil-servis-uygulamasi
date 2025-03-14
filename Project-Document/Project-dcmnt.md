# Acil Servis Hasta Yönetim Sistemi - Proje Dökümanı

## 1. Proje Tanımı

Bu proje, hastane acil servislerinde hasta kayıt ve takip işlemlerini yönetmek için geliştirilmiş bir C programıdır. Hastaların kayıt edilmesi, triaj sınıflandırması, uygun doktorlara yönlendirilmesi ve HL7 formatında hasta bilgilerinin tutulması amaçlanmıştır.

## 2. Veri Yapıları

### 2.1 Temel Yapılar

```c
typedef struct {
    char name[50];        // Hasta adı
    char surname[50];     // Hasta soyadı
    int age;              // Yaş
    char tc_no[12];       // TC kimlik numarası
    char triaj[10];       // Triaj durumu
    char complaint[100];  // Hasta şikayeti
    char doctor[50];      // Doktor bilgisi
    char diagnosis[100];  // Teşhis
    char medication[100]; // İlaç bilgisi
    char hl7_record[500]; // HL7 kaydı
    int prescription_no;  // Reçete numarası
} Patient;

typedef struct {
    Patient patients[MAX_PATIENTS]; // Hasta dizisi
    int front, rear;                // Kuyruk indeksleri
} Queue;

typedef struct {
    char name[50];       // Doktor adı
    char specialty[50];  // Uzmanlık alanı
} Doctor;
```

## 3. Ana Fonksiyonlar

### 3.1 Kuyruk İşlemleri
- `initQueue()`: Kuyruk başlatma
- `isEmpty()`: Boş kuyruk kontrolü
- `isFull()`: Dolu kuyruk kontrolü
- `enqueue()`: Kuyruğa hasta ekleme
- `dequeue()`: Kuyruktan hasta çıkarma

### 3.2 Hasta İşlemleri
- `addPatient()`: Yeni hasta kaydı oluşturma
- `viewPatient()`: TC kimlik numarasına göre hasta görüntüleme
- `printPatient()`: Hasta bilgilerini yazdırma
- `deletePatient()`: Hasta silme

### 3.3 Doktor İşlemleri
- `initDoctors()`: Doktor listesini başlatma
- `findDoctor()`: Şikayete göre uygun doktor bulma

### 3.4 HL7 İşlemleri
- `createHL7Record()`: HL7 formatında kayıt oluşturma
- `generatePrescriptionNo()`: Reçete numarası üretme

## 4. Sistem Özellikleri

### 4.1 Triaj Sistemi
- **Kırmızı**: Acil müdahale gerektiren
- **Sarı**: Öncelikli tedavi gerektiren
- **Yeşil**: Acil olmayan

### 4.2 Doktor Atama Algoritması

| Şikayet | Doktor Uzmanlığı |
|---------|------------------|
| kalp, göğüs | Kardiyoloji |
| baş ağrısı, sinir | Nöroloji |
| ameliyat, yaralanma | Genel Cerrahi |
| kemik, eklem | Ortopedi |
| öksürük, ateş, kusma | Dahiliye |

### 4.3 HL7 Format Örneği

```
MSH|^~\&|HOSPITAL|ER|LAB|202310101200||ADT^A01|123456|P|2.5
PID|||[Ad]^[Soyad]||[Yaş]|||[TC No]
PV1|||[Doktor]|||||||||||||||||||||||||||||||||||||||||
DG1|||[Teşhis]
RXA|||[İlaç]
PRB|||[Reçete No]
```

## 5. Sistem Akışı
```
1. Hasta kaydı oluşturulur
2. Şikayete göre doktor atanır
3. Otomatik teşhis ve ilaç önerisi yapılır
4. HL7 kaydı oluşturulur
5. Hasta kuyruğa eklenir
```
### 5.1 Sistem Akış Şeması
![SistemAkışŞeması](Project-Document/Flowchart.jpg)

## 6. Kullanıcı Arayüzü

```
Acil Servis Uygulaması
1. Yeni Hasta Ekle
2. Hasta Bilgileri Görüntüle
3. Tüm Hastaları Görüntüle
4. Hasta Sil
5. Çıkış
```

## 7. Kısıtlamalar

- Maksimum 100 hasta kaydı
- 5 doktor tanımlanmıştır
- Veriler kalıcı olarak saklanmamaktadır
- TC kimlik numarası doğrulama yoktur

## 8. Gelecek Geliştirmeler

- Veri tabanı entegrasyonu
- Grafiksel kullanıcı arayüzü
- Triaj önceliğine göre sıralama
- Doktor ve hasta istatistikleri
- Randevu sistemi entegrasyonu
