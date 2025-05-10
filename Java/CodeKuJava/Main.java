import java.util.Scanner;

// Class Mahasiswa
class Mahasiswa {
    private String nama;
    private String nim;
    private String jurusan;

    public Mahasiswa(String nama, String nim, String jurusan) {
        this.nama = nama;
        this.nim = nim;
        this.jurusan = jurusan;
    }

    public String getNama() {
        return nama;
    }

    public void setNama(String nama) {
        this.nama = nama;
    }

    public String getNim() {
        return nim;
    }

    public void setNim(String nim) {
        this.nim = nim;
    }

    public String getJurusan() {
        return jurusan;
    }

    public void setJurusan(String jurusan) {
        this.jurusan = jurusan;
    }

    public void tampilkanInfo() {
        System.out.println("Nama: " + this.nama);
        System.out.println("NIM: " + this.nim);
        System.out.println("Jurusan: " + this.jurusan);
    }
}

class MahasiswaSarjana extends Mahasiswa {
    private String tugasAkhir;

    public MahasiswaSarjana(String nama, String nim, String jurusan, String tugasAkhir) {
        super(nama, nim, jurusan);
        this.tugasAkhir = tugasAkhir;
    }

    public String getTugasAkhir() {
        return tugasAkhir;
    }

    public void setTugasAkhir(String tugasAkhir) {
        this.tugasAkhir = tugasAkhir;
    }

    @Override
    public void tampilkanInfo() {
        super.tampilkanInfo();
        System.out.println("Tingkat: Sarjana");
        System.out.println("Tugas Akhir: " + this.tugasAkhir);
        System.out.println("-----------------------");
    }
}

class MahasiswaMagister extends Mahasiswa {
    private String penelitian;

    public MahasiswaMagister(String nama, String nim, String jurusan, String penelitian) {
        super(nama, nim, jurusan);
        this.penelitian = penelitian;
    }

    public String getPenelitian() {
        return penelitian;
    }

    public void setPenelitian(String penelitian) {
        this.penelitian = penelitian;
    }

    @Override
    public void tampilkanInfo() {
        super.tampilkanInfo();
        System.out.println("Tingkat: Magister");
        System.out.println("Penelitian: " + this.penelitian);
        System.out.println("-----------------------");
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Mahasiswa[] mahasiswaArray = new Mahasiswa[100]; // Array untuk menyimpan mahasiswa
        int jumlahMahasiswa = 0;

        System.out.println("========================================");
        System.out.println("Aplikasi Data Mahasiswa");
        System.out.println("Nama: Arif Rahman Hakim");
        System.out.println("NIM: 23051204218");
        System.out.println("Prodi: TI 2023G");
        System.out.println("========================================");

        while (true) {
            System.out.println("\nMenu:");
            System.out.println("1. Input mahasiswa");
            System.out.println("2. Tampilkan mahasiswa Magister");
            System.out.println("3. Tampilkan mahasiswa Sarjana");
            System.out.println("4. Keluar");
            System.out.print("Pilih opsi: ");
            int pilihan = input.nextInt();
            input.nextLine(); // Mengkonsumsi newline

            switch (pilihan) {
                case 1:
                    System.out.print("Masukkan jumlah mahasiswa yang ingin diinput: ");
                    int jumlah = input.nextInt();
                    input.nextLine(); // Konsumsi newline setelah input integer

                    for (int i = 0; i < jumlah; i++) {
                        System.out.println("\nInput data untuk mahasiswa ke-" + (jumlahMahasiswa + 1));

                        System.out.print("Masukkan Nama: ");
                        String nama = input.nextLine();

                        System.out.print("Masukkan NIM: ");
                        String nim = input.nextLine();

                        System.out.print("Masukkan Jurusan: ");
                        String jurusan = input.nextLine();

                        System.out.print("Apakah mahasiswa ini Sarjana atau Magister? (S/M): ");
                        char tipe = input.next().charAt(0);
                        input.nextLine(); // Konsumsi newline

                        if (tipe == 'S' || tipe == 's') {
                            System.out.print("Masukkan Tugas Akhir: ");
                            String tugasAkhir = input.nextLine();
                            mahasiswaArray[jumlahMahasiswa] = new MahasiswaSarjana(nama, nim, jurusan, tugasAkhir);
                        } else if (tipe == 'M' || tipe == 'm') {
                            System.out.print("Masukkan Penelitian: ");
                            String penelitian = input.nextLine();
                            mahasiswaArray[jumlahMahasiswa] = new MahasiswaMagister(nama, nim, jurusan, penelitian);
                        } else {
                            System.out.println("Input tidak valid.");
                            i--; // Ulangi input
                        }
                        jumlahMahasiswa++;
                    }
                    break;

                case 2:
                    System.out.println("\nData Mahasiswa Magister:");
                    for (int i = 0; i < jumlahMahasiswa; i++) {
                        if (mahasiswaArray[i] instanceof MahasiswaMagister) {
                            mahasiswaArray[i].tampilkanInfo();
                        }
                    }
                    break;

                case 3:
                    System.out.println("\nData Mahasiswa Sarjana:");
                    for (int i = 0; i < jumlahMahasiswa; i++) {
                        if (mahasiswaArray[i] instanceof MahasiswaSarjana) {
                            mahasiswaArray[i].tampilkanInfo();
                        }
                    }
                    break;

                case 4:
                    System.out.println("Keluar dari aplikasi...");
                    input.close();
                    System.exit(0);

                default:
                    System.out.println("Pilihan tidak valid. Silakan coba lagi.");
            }
        }
    }
}
