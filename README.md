# minitalk
### Echole 42 minitalk projesi.
Minitalk **Echole 42** eğitim sürecinde ikinci halkada karşımıza çıkan, bir sinyal ve haberleşme projesidir.
Bu projede halihazırda linux ve macos sistemlerde tanımlı olan **SIGUSR1** ve **SIGUSR2** sinyallerini kullanarak,
haberleşmeyi öğreneceğiz.

Projeyi build etmek için:
1) `make` yada `make all` komutunu kullanın ve build edin.
2) Keyfi olarak, build ettikten sonra `make clean` atabilrsiniz.

Programı ayağa kaldırırken:
1) İlk olarak `./server` komutuyla serveri çalıştırmalısınız.
2) Server çalıştıktan sonra terminale kendi **pid** sini yazdırır ardından SIGUSR1 ve SIGUSR2 sinyallerini dinlemeye başlar.
3) Farklı bir terminal ekranı açın ve `./client pid message` komutu ile gerekli parametreleri girip çalıştırın.

Kurulum bu kadar.
