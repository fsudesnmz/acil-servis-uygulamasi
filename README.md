# Acil Servis Hasta Yönetim Sistemi

Bu proje, bir hastane acil servisindeki hasta yönetim sürecini simüle eden kapsamlı bir C programıdır. Sistem, hastaların kayıt edilmesi, triaj durumlarının belirlenmesi, şikayetlerine göre uygun doktorlara yönlendirilmesi ve hasta bilgilerinin HL7 formatında kaydedilmesi gibi temel hastane acil servis operasyonlarını içerir.

## İçindekiler

- [Özellikler](#özellikler)
- [Teknik Detaylar](#teknik-detaylar)
- [Sistem Akış Şeması](#sistem-akış-şeması)
- [Sistem Gereksinimleri](#sistem-gereksinimleri)
- [Kullanım](#kullanım)
  - [Yeni Hasta Ekle](#1-yeni-hasta-ekle)
  - [Hasta Bilgileri Görüntüle](#2-hasta-bilgileri-görüntüle)
  - [Eklenen Tüm Hastaları Görüntüle](#3-eklenen-tüm-hastaları-görüntüle)
  - [Hasta Sil](#4-hasta-sil)
- [Veri Yapıları](#veri-yapıları)
- [Fonksiyonlar](#fonksiyonlar)
- [HL7 Entegrasyonu](#hl7-entegrasyonu)
- [Doktor Otomatik Atama Algoritması](#doktor-otomatik-atama-algoritması)
- [Triaj Sistemi](#triaj-sistemi)
- [Bilinen Sorunlar](#bilinen-sorunlar)
- [Lisans](#lisans)

## Özellikler

- **Hasta Kaydı**: Temel demografik bilgiler ve şikayetlerin tutulması
- **Triaj Sınıflandırması**: Hastaların aciliyet durumlarına göre sınıflandırılması (kırmızı, sarı, yeşil)
- **Otomatik Doktor Ataması**: Şikayetlere göre uzman doktor ataması
- **Dairesel Kuyruk Yapısı**: Verimli hasta sırası yönetimi için dairesel kuyruk veri yapısı
- **HL7 Formatında Raporlama**: Uluslararası sağlık standardı HL7 formatında hasta kayıtları
- **Otomatik Teşhis Önerisi**: Şikayetlere göre ön teşhis oluşturma
- **İlaç Önerisi**: Teşhise göre uygun ilaç önerileri
- **Benzersiz Reçete Numarası**: Her hasta için otomatik üretilen benzersiz reçete numaraları
- **TC Kimlik Doğrulama**: TC kimlik numarasına göre hasta arama ve doğrulama
- **Hasta Silme ve Güncelleme**: Kayıtlı hastaların bilgilerini silme ve güncelleme

## Teknik Detaylar

Bu sistem, aşağıdaki C programlama konseptlerini kullanmaktadır:

- Yapılar (Structs) ve Özel Veri Tipleri
- Dairesel Kuyruk Veri Yapısı
- Dinamik Bellek Yönetimi
- Dosya İşlemleri (İleriki versiyonlarda eklenecek)
- Dize İşlemleri ve Metin Manipülasyonu
- Rastgele Sayı Üretimi
- Pointer İşlemleri
- Koşullu Mantık ve Karar Verme Algoritmaları
  
## Sistem Akış Şeması

Sistemin genel çalışma prensibi aşağıdaki akış şemasında gösterilmiştir:

![Acil Servis Akış Şeması](images/flowchart.png)

## Sistem Gereksinimleri

- C Derleyicisi (GCC 5.0+ önerilir)
- Standard C Kütüphaneleri:
  - stdio.h: Standard giriş/çıkış işlemleri için
  - stdlib.h: Bellek yönetimi ve dönüşüm fonksiyonları için
  - string.h: String manipülasyonu için
  - time.h: Rastgele sayı üretimi için
- En az 64MB RAM
- 10MB boş disk alanı

##  Kullanım

Program çalıştırıldığında aşağıdaki ana menü görüntülenir:

```
Acil Servis Uygulaması
1. Yeni Hasta Ekle
2. Hasta Bilgileri Görüntüle (Belirli Bir Hasta)
3. Eklenen Tüm Hastaları Görüntüle
4. Hasta Sil
5. Çıkış
Seçiminiz:
```

### 1. Yeni Hasta Ekle

Bu menü seçeneği ile yeni bir hasta kaydı oluşturabilirsiniz:

```
Hasta Adı: Ahmet
Hasta Soyadı: Yılmaz
Yaş: 45
TC Kimlik No: 12345678910
Triaj Durumu (kırmızı/sarı/yeşil): sarı
Hasta Şikayeti (öksürük, ateş, kusma, vs.): göğüs ağrısı, nefes darlığı
```

Bilgiler girildikten sonra, sistem otomatik olarak:
- Hasta şikayetine göre uygun doktoru atar (örneğin göğüs ağrısı için kardiyoloji uzmanı)
- Olası teşhis önerir
- Teşhise göre ilaç önerir
- Benzersiz bir reçete numarası oluşturur
- HL7 formatında hasta kaydı oluşturur

### 2. Hasta Bilgileri Görüntüle

TC kimlik numarası girerek belirli bir hastanın tüm bilgilerini görüntüleyebilirsiniz:

```
Görüntülenecek hastanın TC kimlik numarasını girin: 12345678910

Hasta bulundu:
Hasta Adı: Ahmet Yılmaz
Yaş: 45
TC Kimlik No: 12345678910
Triaj Durumu: sarı
Şikayet: göğüs ağrısı, nefes darlığı
Yönlendirilen Doktor: Dr. Ahmet Yılmaz
Teşhis: Kalp krizi riski
İlaç: Aspirin 100 mg
Reçete No: 123456
HL7 Kaydı:
MSH|^~\&|HOSPITAL|ER|LAB|202310101200||ADT^A01|123456|P|2.5
PID|||Ahmet^Yılmaz||45|||12345678910
PV1|||Dr. Ahmet Yılmaz||||||||||||||||||||||||||||||||||||||||||||||||||||
DG1|||Kalp krizi riski
RXA|||Aspirin 100 mg
PRB|||123456
--------------------------
```

### 3. Eklenen Tüm Hastaları Görüntüle

Bu seçenek, sisteme kaydedilmiş tüm hastaların bilgilerini listeler:

```
Eklenen Tüm Hastalar:
Hasta Adı: Ahmet Yılmaz
Yaş: 45
TC Kimlik No: 12345678910
Triaj Durumu: sarı
...

Hasta Adı: Ayşe Demir
Yaş: 28
TC Kimlik No: 10987654321
Triaj Durumu: yeşil
...
```

### 4. Hasta Sil

TC kimlik numarasını girerek bir hastayı sistemden silebilirsiniz:

```
Silinecek hastanın TC kimlik numarasını girin: 12345678910

Hasta bulundu ve siliniyor:
[Hasta bilgileri görüntülenir]
Hasta başarıyla silindi.
```

##  Veri Yapıları

### Patient Yapısı

```c
typedef struct {
    char name[50];         // Hasta adı
    char surname[50];      // Hasta soyadı
    int age;               // Yaş
    char tc_no[12];        // TC kimlik numarası (11 hane + null karakter)
    char triaj[10];        // Triaj durumu: kırmızı, sarı, yeşil
    char complaint[100];   // Hasta şikayeti
    char doctor[50];       // Yönlendirilen doktor
    char diagnosis[100];   // Teşhis (doktor tarafından girilir)
    char medication[100];  // İlaç (doktor tarafından girilir)
    char hl7_record[500];  // HL7 formatında hasta kaydı
    int prescription_no;   // Reçete numarası
} Patient;
```

### Kuyruk Yapısı

```c
typedef struct {
    Patient patients[MAX_PATIENTS];  // Hasta dizisi (maksimum 100 hasta)
    int front, rear;                // Kuyruğun ön ve arka indeksleri
} Queue;
```

### Doktor Yapısı

```c
typedef struct {
    char name[50];         // Doktor adı
    char specialty[50];    // Uzmanlık alanı
} Doctor;
```

## Fonksiyonlar

### Kuyruk İşlemleri

- `initQueue()`: Kuyruk veri yapısını başlatır
- `isEmpty()`: Kuyruğun boş olup olmadığını kontrol eder
- `isFull()`: Kuyruğun dolu olup olmadığını kontrol eder
- `enqueue()`: Kuyruğa yeni bir hasta ekler
- `dequeue()`: Kuyruktan bir hasta çıkarır
- `printQueue()`: Kuyruktaki tüm hastaları listeler
- `deletePatient()`: TC kimlik numarasına göre hastayı kuyruktan siler

### Hasta İşlemleri

- `addPatient()`: Sisteme yeni bir hasta ekler
- `viewPatient()`: TC kimlik numarasına göre hasta bilgilerini görüntüler
- `printPatient()`: Hasta bilgilerini ekrana yazdırır
- `fillDoctorInfo()`: Hastanın şikayetine göre otomatik olarak teşhis ve ilaç bilgilerini doldurur
- `createHL7Record()`: Hasta bilgilerinden HL7 formatında kayıt oluşturur
- `generatePrescriptionNo()`: Rastgele benzersiz reçete numarası üretir

### Doktor İşlemleri

- `initDoctors()`: Sisteme varsayılan doktorları ekler
- `findDoctor()`: Hasta şikayetine göre uygun doktoru bulur

## HL7 Entegrasyonu

Sistem, hasta kayıtlarını uluslararası sağlık veri standardı olan HL7 (Health Level Seven) formatında oluşturur:

```
MSH|^~\&|HOSPITAL|ER|LAB|202310101200||ADT^A01|123456|P|2.5
PID|||[Hasta Adı]^[Hasta Soyadı]||[Yaş]|||[TC Kimlik No]
PV1|||[Doktor]||||||||||||||||||||||||||||||||||||||||||||||||||||
DG1|||[Teşhis]
RXA|||[İlaç]
PRB|||[Reçete No]
```

Bu format, diğer sağlık sistemleriyle entegrasyon sağlar ve şu segmentleri içerir:
- MSH: Mesaj Başlığı
- PID: Hasta Tanımlama
- PV1: Hasta Ziyareti
- DG1: Teşhis
- RXA: İlaç Bilgileri
- PRB: Reçete Bilgileri

## Doktor Otomatik Atama Algoritması

Sistem, hastaları şikayetlerine göre uygun doktorlara yönlendirir:

| Şikayet İçeriği | Atanan Uzmanlık |
|-----------------|-----------------|
| kalp, göğüs | Kardiyoloji |
| baş ağrısı, sinir | Nöroloji |
| ameliyat, yaralanma | Genel Cerrahi |
| kemik, eklem | Ortopedi |
| öksürük, ateş, kusma | Dahiliye |
| Diğer şikayetler | Dahiliye (varsayılan) |

## Triaj Sistemi

Sistem, hastaları aciliyet durumlarına göre üç kategoride sınıflandırır:

- **Kırmızı**: Acil müdahale gerektiren, hayati tehlikesi olan hastalar
- **Sarı**: Acil olmayan ancak öncelikli tedavi gerektiren hastalar  
- **Yeşil**: Acil olmayan, bekleyebilecek durumdaki hastalar

## Bilinen Sorunlar

- Büyük veri miktarlarında performans sorunları
- Triaj sıralaması henüz tam olarak uygulanmamıştır
- TC kimlik numarası doğrulama algoritması yoktur
- Bazı durumlarda bellek sızıntısı meydana gelebilir

## Lisans

Bu proje [MIT Lisansı](LICENSE) altında lisanslanmıştır.
