<div align="center">

# minitalk

**SIGUSR1 ve SIGUSR2 sinyalleri aracılığıyla iki proses arasında mesaj iletimi.**

[![Language](https://img.shields.io/badge/language-C-00599C?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![School](https://img.shields.io/badge/42-Kocaeli-00BABC?style=for-the-badge)](https://42kocaeli.com.tr/)
[![Norm](https://img.shields.io/badge/norminette-passing-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)

</div>

---

## Proje Hakkında

`minitalk`, Unix sinyallerini kullanarak iki proses arasında string iletimi sağlayan bir 42 Kocaeli projesidir. Standart IPC (inter-process communication) kanalları yerine yalnızca **`SIGUSR1`** ve **`SIGUSR2`** sinyalleri kullanılır — her sinyal bir bit temsil eder.

---

## Mimari

```
CLIENT                         SERVER
  │                               │
  │  PID al                       │  Başlat
  │                               │  PID yaz
  │                               │  Sinyal bekle
  │                               │
  │──── SIGUSR2 (bit=1) ─────────►│  bit: 1
  │──── SIGUSR1 (bit=0) ─────────►│  bit: 0
  │──── SIGUSR2 (bit=1) ─────────►│  bit: 1
  │         ... (8 bit) ...       │
  │◄─── SIGUSR1 (onay) ──────────│  karakter hazır → yaz
  │                               │
  │  (sonraki karakter)           │
  │──── ...8 bit... ─────────────►│
  │◄─── SIGUSR1 (onay) ──────────│
```

---

## Bit Kodlama

Her karakter 8 sinyal olarak iletilir (MSB önce):

```
'A' = 01000001

Bit 7 (MSB) = 0 → SIGUSR1
Bit 6       = 1 → SIGUSR2
Bit 5       = 0 → SIGUSR1
Bit 4       = 0 → SIGUSR1
Bit 3       = 0 → SIGUSR1
Bit 2       = 0 → SIGUSR1
Bit 1       = 0 → SIGUSR1
Bit 0 (LSB) = 1 → SIGUSR2
```

Server tarafında bit birikimleri:
```c
c |= 1 << (7 - recived_count);   // SIGUSR2 = bit 1
// SIGUSR1 geldiğinde hiçbir şey yapılmaz = bit 0
```

---

## Kurulum

```bash
# Klonla
git clone https://github.com/Sayicon/minitalk.git
cd minitalk

# Derle
make

# Temizlik
make clean    # .o dosyaları
make fclean   # .o + binary'ler
make re       # yeniden derle
```

---

## Kullanım

### 1. Server'ı Başlat

```bash
./server
```

```
Server PID: 12345
Sinyal bekleniyor...
```

### 2. Client ile Mesaj Gönder

```bash
./client 12345 "Merhaba, Dünya!"
```

Server terminalinde görünür:
```
Merhaba, Dünya!
```

> Farklı iki terminal penceresi gerekir.

---

## Nasıl Çalışır?

### Server (`ft_server.c`)

1. `sigaction()` ile hem `SIGUSR1` hem `SIGUSR2` için handler kaydeder
2. `SA_SIGINFO` bayrağı sayesinde gönderenin PID'ini `si_pid` ile öğrenir
3. Her sinyal geldiğinde `ft_create_char_by_bits` çağrılır:
   - `SIGUSR2` → ilgili bit 1'e set edilir
   - `SIGUSR1` → ilgili bit 0 kalır
4. 8 bit tamamlanınca karakter yazdırılır, `'\0'` gelince `\n` basılır
5. Her bit alındığında client'a `SIGUSR1` onay sinyali gönderilir

### Client (`ft_client.c`)

1. PID argümanını doğrular
2. Her karakteri 8 bite çevirir, MSB'den başlar
3. Her bit için `kill(pid, SIGUSR1/SIGUSR2)` çağırır
4. `ft_server_affirmation` handler'ı onay sinyalini bekler (`g_signal_flag`)
5. Onay gelmeden sonraki bit gönderilmez (senkronizasyon)
6. Mesaj bittikten sonra `'\0'` karakteri iletilir

---

## Dosya Yapısı

```
minitalk/
├── ft_client.c   # Client: mesaj gönderici
├── ft_server.c   # Server: sinyal alıcı ve yazdırıcı
├── Makefile
└── README.md
```

---

## Sinyaller Hakkında

| Sinyal | Değer | Kullanım |
|--------|-------|----------|
| `SIGUSR1` | 10 | bit=0 veya onay sinyali |
| `SIGUSR2` | 12 | bit=1 |

> POSIX'te `SIGUSR1` ve `SIGUSR2` kullanıcı tanımlı sinyallerdir. Linux ve macOS'ta varsayılan olarak mevcuttur.

---

<div align="center">

*42 Kocaeli — minitalk projesi*

[![GitHub](https://img.shields.io/badge/GitHub-Sayicon-181717?style=flat-square&logo=github)](https://github.com/Sayicon)

</div>
