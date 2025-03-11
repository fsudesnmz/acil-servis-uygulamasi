# Acil Servis Hasta Yönetim Sistemi

Bu proje, bir hastane acil servisindeki hasta yönetim sürecini simüle eden C programıdır. Sistem, hastaların kayıt edilmesi, triaj durumlarının belirlenmesi, şikayetlerine göre uygun doktorlara yönlendirilmesi ve hasta bilgilerinin HL7 formatında kaydedilmesi gibi özellikleri içermektedir.

## Özellikler

- Hasta bilgilerinin (ad, soyad, yaş, TC kimlik numarası, triaj durumu, şikayet) kaydedilmesi
- Hasta şikayetine göre otomatik doktor ataması
- Hasta bilgilerinin TC kimlik numarasına göre görüntülenmesi
- Kuyruk yapısı kullanarak hasta sırasının yönetimi
- HL7 formatında hasta kaydı oluşturma
- Otomatik teşhis ve ilaç önerisi
- Otomatik reçete numarası oluşturma
- Hastaların sistemden silinmesi

## Sistem Gereksinimleri

- C Derleyicisi (GCC önerilir)
- Standard C Kütüphaneleri (stdio.h, stdlib.h, string.h, time.h)

## Kullanım

Program çalıştırıldığında aşağıdaki menü görüntülenir:

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
Bu seçenek, yeni bir hasta kaydı oluşturmanızı sağlar. Hasta adı, soyadı, yaşı, TC kimlik numarası, triaj durumu ve şikayeti girilir. Sistem otomatik olarak uygun doktoru atar, teşhis ve ilaç önerisi yapar, reçete numarası oluşturur ve HL7 formatında kayıt oluşturur.

### 2. Hasta Bilgileri Görüntüle
TC kimlik numarası girilerek belirli bir hastanın bilgileri görüntülenebilir.

### 3. Eklenen Tüm Hastaları Görüntüle
Sisteme kayıtlı tüm hastaların bilgilerini listeler.

### 4. Hasta Sil
TC kimlik numarası girilerek belirli bir hasta sistemden silinebilir.

### 5. Çıkış
Programdan çıkış yapılır.

## Veri Yapıları

### Patient Yapısı
```c
typedef struct {
    char name[50];
    char surname[50];
    int age;
    char tc_no[12]; // TC kimlik numarası
    char triaj[10]; // Triaj durumu: kırmızı, sarı, yeşil
    char complaint[100]; // Hasta şikayeti
    char doctor[50]; // Yönlendirilen doktor
    char diagnosis[100]; // Teşhis
    char medication[100]; // İlaç
    char hl7_record[500]; // HL7 formatında hasta kaydı
    int prescription_no; // Reçete numarası
} Patient;
```

### Kuyruk Yapısı
```c
typedef struct {
    Patient patients[MAX_PATIENTS];
    int front, rear;
} Queue;
```

### Doktor Yapısı
```c
typedef struct {
    char name[50];
    char specialty[50]; // Uzmanlık alanı
} Doctor;
```

## Lisans

Bu proje MIT lisansı altında lisanslanmıştır. Daha fazla bilgi için `LICENSE` dosyasına bakınız.
