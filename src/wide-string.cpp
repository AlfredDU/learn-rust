#include <codecvt> // This header is necessary for convert "std::wstring" to "std::string".

#include <string>
#include <array>
#include <iostream>
#include <cstdlib>



int main(int argc, char* argv[])
{
    /* On the platform of OS X, std::string instance is automatically encoded in UTF-8. */
    std::string messi = "莱奥内尔•梅西";
    
    std::cout << "Given a literal Chinese string: \"" << messi << "\"" << std::endl;
    std::cout << "If assigned to a std::string instance, then paradoxically the length is: "
        << messi.length() << std::endl;
    
    std::wstring w_messi = L"莱奥内尔•梅西";
    std::cout << "If assigned to a std::wstring instance, then the length is just what expected: "
        << w_messi.length() << std::endl;
    
    // Wide string operations.
    std::wstring w_messi_son = L"蒂亚戈•梅西";
    std::wstring w_messi_familyname =
        w_messi.substr(w_messi.find(L'•') + 1, w_messi.length() - w_messi.find(L'•') - 1);
    std::wstring w_messi_son_familyname =
        w_messi_son.substr(w_messi_son.find(L'•') + 1, w_messi_son.length() - w_messi_son.find(L'•') - 1);
    
    // Convert wide string.
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > converter; // Template std::codecvt_utf8_utf16 also accepts type "char16_t" & "char32_t", which (I think) are rarely used.
    std::wstring familyname_messi = (w_messi_familyname == w_messi_son_familyname ?
                                     w_messi_familyname : L"");
    std::cout << converter.to_bytes(familyname_messi) << std::endl;
    
    // More examples.
    std::wstring w_schrodinger = L"Schrödinger";
    std::wstring w_mendeleev = L"Менделе́ев";
    
    std::cout << "The letters of Germany string " + converter.to_bytes(w_schrodinger) + " is: ";
    for (std::wstring::size_type i = 0; i < w_schrodinger.length(); i++) {
        std::cout << converter.to_bytes(w_schrodinger.substr(i, 1));
        if (i < w_schrodinger.length() - 1) {
            std::cout << "-";
        }
    }
    std::cout << std::endl;
    
    std::cout << "The letters of Russian string " + converter.to_bytes(w_mendeleev) + " is: ";
    for (std::wstring::size_type i = 0; i < w_mendeleev.length(); i++) {
        std::cout << converter.to_bytes(w_mendeleev.substr(i, 1));
        if (i < w_mendeleev.length() - 1) {
            std::cout << "-";
        }
    }
    std::cout << std::endl << "Note that \'" + converter.to_bytes(w_mendeleev.substr(7, 1)) + "\' is regarded as a letter" << std::endl;
    
        return EXIT_SUCCESS;
}