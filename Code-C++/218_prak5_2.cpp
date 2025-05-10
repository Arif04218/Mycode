#include <iostream>
#include <string>

using namespace std;

// Struktur data supir
struct Supir {
    int id;
    string nama;
    string tglLahir;
    char kelamin;
    string alamat;
};

// Kelas Node untuk LinkedList
class Node {
public:
    Supir data;
    Node* next;

    Node(const Supir& supir) {
        data = supir;
        next = nullptr;
    }
};

// Kelas LinkedList untuk menyimpan data supir
class LinkedList {
private:
    Node* head;
    Node* tail;
    Node* current;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~LinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    // Menambahkan supir baru
    void tambahSupir(const Supir& supir) {
        Node* newNode = new Node(supir);
        if (!head) {
            head = newNode;
            tail = newNode;
            current = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Menampilkan data supir saat ini
    void tampilkanSupir() {
        Supir currentSupir = current->data;
        cout << "|-------------------------|" << endl;
        cout << "|Nama : " << currentSupir.nama << endl;
        cout << "|Id : " << currentSupir.id << endl;
        cout << "|Tgl Lahir: " << currentSupir.tglLahir << endl;
        cout << "|Kelamin : " << currentSupir.kelamin << endl;
        cout << "|Alamat : " << currentSupir.alamat << endl;
        cout << "|-------------------------|" << endl;
    }

    // Melanjutkan ke supir berikutnya
    void nextSupir() {
        if (current->next) {
            current = current->next;
        } else {
            current = head;
        }
    }

    // Kembali ke supir sebelumnya
    void previousSupir() {
        Node* prev = head;
        while (prev->next != current) {
            prev = prev->next;
        }
        current = prev;
    }

    // Menghapus supir dengan id tertentu
    void hapusSupir(int id) {
        Node* prev = nullptr;
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data.id == id) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    head = temp->next;
                }
                delete temp;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    // Mencari supir berdasarkan id
    Supir* cariSupir(int id) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data.id == id) {
                return &(temp->data);
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

// Fungsi untuk menghasilkan id supir berdasarkan aturan yang diberikan
int generateSupirId(const string& nama, char kelamin, const string& tglLahir) {
    int id = abs(nama[0] - nama[nama.length() - 1]); // Menggunakan nilai absolut untuk menghindari id negatif
    id *= 10; // Membuat dua digit pertama
    id += (kelamin == 'l' || kelamin == 'L') ? 1 : 0; // Menambahkan digit ketiga
    // Menambahkan digit keempat berdasarkan tgl lahir
    int tgl = stoi(tglLahir.substr(0, 2));
    int bln = stoi(tglLahir.substr(3, 2));
    int thn = stoi(tglLahir.substr(6, 4));
    id += (tgl + bln + thn) % 9;
    // Digit kelima ditetapkan 0 sementara
    return id;
}

// Fungsi untuk menampilkan menu admin
void tampilkanMenuAdmin() {
    cout << "1. Tambah Supir\n";
    cout << "2. Hapus Supir\n";
    cout << "3. Ubah Supir\n";
    cout << "4. Tampilkan Data Supir\n";
    cout << "5. Keluar\n";
}

// Fungsi untuk menampilkan menu user
void tampilkanMenuUser() {
    cout << "1. Tampilkan Data Supir\n";
    cout << "2. Pilih Supir untuk Order\n";
    cout << "3. Keluar\n";
}

int main() {
    LinkedList linkedList;

    // Menambahkan data supir contoh
    Supir supir1 = { generateSupirId("Kim Jatim Park", 'L', "12-02-2001"), "Kim Jatim Park", "12-02-2001", 'L', "Surabaya" };
    linkedList.tambahSupir(supir1);

    // Menu
    int choice;
    bool isAdmin = false;
    do {
        if (isAdmin) {
            tampilkanMenuAdmin();
        } else {
            tampilkanMenuUser();
        }
        cout << "Choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                if (isAdmin) {
                    Supir newSupir;
                    cout << "Nama: ";
                    cin >> newSupir.nama;
                    cout << "Tanggal Lahir (dd-mm-yyyy): ";
                    cin >> newSupir.tglLahir;
                    cout << "Kelamin (l/L untuk Laki-laki, p/P untuk Perempuan): ";
                    cin >> newSupir.kelamin;
                    cout << "Alamat: ";
                    cin >> newSupir.alamat;
                    newSupir.id = generateSupirId(newSupir.nama, newSupir.kelamin, newSupir.tglLahir);
                    linkedList.tambahSupir(newSupir);
                    cout << "Supir berhasil ditambahkan!" << endl;
                } else {
                    linkedList.tampilkanSupir();
                }
                break;
            }
            case 2: {
                if (isAdmin) {
                    int idToDelete;
                    cout << "Masukkan ID Supir yang ingin dihapus: ";
                    cin >> idToDelete;
                    linkedList.hapusSupir(idToDelete);
                    cout << "Supir dengan ID " << idToDelete << " berhasil dihapus!" << endl;
                } else {
                    // Pilihan untuk user untuk memilih supir untuk order
                    // Belum diimplementasikan
                    cout << "Fitur ini akan segera hadir!" << endl;
                }
                break;
            }
            case 3: {
                if (isAdmin) {
                    // Ubah Supir
                    // Belum diimplementasikan
                    cout << "Fitur ini akan segera hadir!" << endl;
                } else {
                    return 0; // Keluar dari program
                }
                break;
            }
            case 4: {
                if (isAdmin) {
                    // Tampilkan Data Supir
                    Supir* currentSupir = &(linkedList.cariSupir(linkedList.tampilkanSupir());
                    cout << "Nama: " << currentSupir->nama << endl;
                    cout << "ID: " << currentSupir->id << endl;
                    cout << "Tanggal Lahir: " << currentSupir->tglLahir << endl;
                    cout << "Kelamin: " << currentSupir->kelamin << endl;
                    cout << "Alamat: " << currentSupir->alamat << endl;
                } else {
                    // User tidak perlu melakukan apa-apa
                }
                break;
            }
            case 5: {
                if (isAdmin) {
                    isAdmin = false; // Ubah menjadi mode user
                } else {
                    isAdmin = true; // Ubah menjadi mode admin
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 3);

    return 0;
}
