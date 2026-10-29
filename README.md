# BMT317 - Sıralama Algoritmaları Performans Karşılaştırması

Bu proje, Gazi Üniversitesi Teknoloji Fakültesi BMT317 Algoritmalar dersi kapsamında, farklı sıralama algoritmalarının performanslarını (çalışma süresi, karşılaştırma sayısı ve veri hareketi) deneysel olarak analiz etmek amacıyla hazırlanmıştır.

## 1. Proje Yapısı (Sınıflar ve Dosyalar)

Proje, kodun okunabilirliğini ve yönetilebilirliğini artırmak amacıyla modüler bir yapıda, farklı kaynak dosyalarına (`.cpp` ve `.h`) ayrılarak geliştirilmiştir:

- **`src/algorithms.h` & `src/algorithms.cpp`**: Selection, Insertion, Bubble, Shell, Quick, Merge ve Heap sıralama algoritmalarını içerir.
- **`src/utils.h` & `src/utils.cpp`**: Veri kümelerinin (Rastgele, Sıralı, Ters Sıralı, Kısmen Sıralı) üretilmesi, dizilerin sıralı olup olmadığının kontrol edilmesi ve performans metriklerinin tutulması için gerekli yardımcı veri yapıları ve fonksiyonları barındırır.
- **`src/main.cpp`**: Test senaryolarının çalıştırıldığı ana dosyadır. Belirlenen boyutlardaki verileri üretir, algoritmaları çağırır, zamanlayıcı ile 5 tekrar yaparak ölçümleri gerçekleştirir ve sonuçları `deney_sonuclari.csv` dosyasına yazar.
- **`deney_sonuclari.csv`**: Deneyler sonucunda elde edilen ham veri tablosu.
- **`BMT317_Proje_Raporu.pdf`**: Deney verilerine dayanarak hazırlanan performans karşılaştırma raporu.

## 2. Deney Ortamı (Sistem Özellikleri)
Adil bir karşılaştırma ve sonuçların tekrarlanabilirliği adına, testlerin gerçekleştirildiği sistem özellikleri aşağıda belirtilmiştir:
- **İşlemci (CPU):** 11th Gen Intel(R) Core(TM) i9-11900F @ 2.50GHz
- **RAM:** 32,0 GB
- **İşletim Sistemi:** Windows 11
- **Programlama Dili:** C++ (C++20)
- **Derleyici / Çalışma Ortamı:** MinGW (GCC)
- **IDE:** CLion 2024.2.2

## 3. Önemli Algoritma Kararları
- **Quick Sort Pivot Yöntemi:** Varsayılan Quick Sort algoritmasında stack overflow sorununu önlemek için **orta eleman** pivot olarak seçilmiştir. Bonus çalışması kapsamında ise **ilk eleman** pivot seçilerek `Quick_FirstPivot` adıyla ayrıca test edilmiştir.
- **Shell Sort Gap Dizisi:** Varsayılan olarak klasik **n/2** dizisi kullanılmıştır. Bonus çalışması kapsamında ise **Knuth'un (3x+1)** dizisi kullanılmış ve `Shell_Knuth` adıyla ayrıca test edilmiştir.
- **O(n²) Algoritmalar İçin Limit:** Yönerge gereği aşırı uzun süren Selection, Insertion ve Bubble Sort algoritmaları 50.000 ve 100.000 boyutlarında atlanmış, tablolara "Limit Aşımı" olarak kaydedilmiştir.

## 4. Kurulum, Derleme ve Çalıştırma
Proje CMake tabanlı bir CLion projesi olarak geliştirilmiştir. Testleri tekrarlamak için aşağıdaki adımları izleyebilirsiniz:

**CLion Üzerinden Çalıştırma:**
1. CLion'da projeyi `Open` diyerek klasör olarak açın.
2. CMake profili otomatik olarak yüklenecektir. Sağ üst köşeden `SortingAlgorithmsComparison` hedefini (target) seçin.
3. Çalıştırmak için `Run` butonuna basın.
4. Konsolda hangi boyutların işlendiği adım adım yazacak ve bitiminde proje kök dizininde `deney_sonuclari.csv` dosyası oluşacaktır.