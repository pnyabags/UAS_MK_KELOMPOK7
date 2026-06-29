# Final Proyek IOT 
- Mata Kuliah: Mikrokontroler 
- Dosen Pengampu: Muhammad Ikhwan Fathulloh
  
## Kelompok
Dikembangkan oleh Kelompok 7
- Ketua: Bagas Arya Putra - 23552011328 [Github](https://github.com/pnyabags)
- Anggota 1: Mochammad Raffi Fadhillah - 23552011066 [Github](https://github.com/Hoshirodesu) 
- Anggota 2: Rafi Nur Muhammad Fauzi - 23552011307 [Github](https://github.com/RafiNur06)
  
## Judul Studi Kasus
**Lampu Ajaib**


## Penjelasan Studi Kasus
Pada umumnya lampu masih dikendalikan menggunakan saklar manual sehingga pengguna harus datang langsung ke lokasi untuk menyalakan atau mematikannya. Kondisi ini kurang efisien ketika pengguna sedang berada di luar rumah atau ingin mengontrol perangkat dari jarak jauh. Maka dibuat proyek lampu ajaib yang dapat dinyalakan dan dimatikan dari mana saja menggunakan protokol MQTT melalui internet. Nama "Lampu Ajaib" dipilih karena pengguna cukup memberikan perintah dari perangkat seperti smartphone atau laptop, kemudian lampu akan secara otomatis.

Lampu dikendalikan melalui web service yang berjalan pada ESP32. ESP32 menerima permintaan (HTTP request) dari browser, kemudian mengontrol modul relay yang berfungsi sebagai saklar elektronik untuk menyalakan atau mematikan lampu.

## Fitur
- Bisa kontrol lampu dari jarak jauh ✔️
- Lampu Memiliki Daya tambahan seperti baterai. ✔️
- Pengisian daya baterai menggunakan matahari melalui solar panel. ✔️

## Komponen IOT

| No | Komponen | Jumlah | Fungsi |
|:--:|----------|:------:|--------|
| 1 | ESP32 DevKit V1 | 1 | Mikrokontroler utama yang menjalankan web service dan mengendalikan relay melalui GPIO27. |
| 2 | Module 1 Channel Relay 5V | 1 | Berfungsi sebagai saklar elektronik untuk menghubungkan atau memutus arus menuju lampu. |
| 3 | LED HPL HEATSINK 1W | 2 | Lampu sebagai output sistem yang dikendalikan oleh relay. |
| 4 | Panel Surya Mini | 2 | Mengubah energi matahari menjadi energi listrik untuk mengisi baterai. |
| 5 | Module Charger 5V | 1 | Mengisi baterai lithium sekaligus memberikan proteksi overcharge dan overdischarge. |
| 6 | Module Step Up Dc Boost Converter 1-5V to 5V | 1 | Menaikkan tegangan baterai menjadi 5V untuk menyuplai ESP32. |
| 7 | Mini 360 Small Adjustable Dc Step Down 2A 5V-23V to 1V-7V | 1 | Mengatur daya yang keluar dari led. |
| 8 | Baterai Lithium | 1 | Menyimpan energi listrik sebagai sumber daya utama sistem. |
| 9 | Breadboard | 1 | Media pemasangan rangkaian sementara tanpa penyolderan. |

## Alur Kerja
- Panel surya menghasilkan energi listrik ketika terkena cahaya.
- Energi listrik masuk ke modul TP4056 untuk mengisi baterai lithium.
- Baterai menjadi sumber daya utama sistem.
- Modul Step-Up menaikkan tegangan baterai menjadi 5V agar ESP32 dapat bekerja dengan stabil.
- ESP32 terhubung ke jaringan WiFi dan menjalankan web service (atau MQTT pada versi lain dari proyekmu).
- Ketika pengguna menekan tombol ON atau OFF pada halaman web, ESP32 mengubah kondisi GPIO27.
- GPIO27 mengendalikan relay.
- Relay menghubungkan atau memutus aliran listrik menuju LED HPL sehingga lampu menyala atau mati.




## Tampilan Hardware
<img width="3264" height="2448" alt="IMG-20260626-WA0031" src="https://github.com/user-attachments/assets/3f95e535-fc55-426a-90bd-17e9c3456ef8" />

Fakultas Industri Kreatif, Departemen Teknik Informatika,  
Universitas Teknologi Bandung, 2026
