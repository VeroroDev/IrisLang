#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <filesystem>

namespace Iris
{
    using abool = std::atomic<bool>;

    using u8 = std::uint8_t;

    using u64 = std::uint64_t;

    using f64 = double;

    using au64 = std::atomic<std::uint64_t>;

    enum class Measurement : u8
    {
        Nanoseconds,
        Microseconds,
        Milliseconds
    };

    #define IsSpace '\n':case ' '
    #define IsNumeric '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9'
    #define IsAlpha '_':case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':case 'y':case 'z'
    #define IsAlphanumeric IsNumeric:case IsAlpha
    #define Errore(x) ALog("\n\nerror at '" + EyeFile + "', " + std::to_string(ln) + " : " + std::to_string(ch) + " -> " + x);goto ep
    #define Errori(x) ALog("\n\nerror at '" + FileIds[ff] + "', " + std::to_string(ln) + " : " + std::to_string(ch) + " -> " + x);goto ep

    class Pair
    {
    private:
        u64 f = 14695981039346656037ull, s = 14695981039346656037ull;
    public:
        [[nodiscard]] inline constexpr Pair() noexcept = default;

        [[nodiscard]] inline constexpr Pair(const u64 First, const u64 Second) noexcept : f(First), s(Second){}

        [[nodiscard]] inline Pair(const std::string& ss) noexcept
        {
            for(const char& c : ss)
            {
                f = f * 1099511628211ull;
                f = f ^ c;
                s = s ^ c;
                s = s * 1099511628211ull;
            }
        }

        inline void operator=(const char& c) noexcept
        {
            f = 14695981039346656037ull * 1099511628211ull;
            f = f ^ c;
            s = 14695981039346656037ull ^ c;
            s = s * 1099511628211ull;
        }

        inline void operator+=(const char& c) noexcept
        {
            f = f * 1099511628211ull;
            f = f ^ c;
            s = s ^ c;
            s = s * 1099511628211ull;
        }

        [[nodiscard]] inline bool operator==(const Pair& p) const noexcept
        {
            return f == p.f && s == p.s;
        }

        [[nodiscard]] inline bool operator!=(const Pair& p) const noexcept
        {
            return f != p.f || s != p.s;
        }

        [[nodiscard]] inline std::string First() const noexcept
        {
            return std::to_string(f);
        }

        [[nodiscard]] inline std::string Second() const noexcept
        {
            return std::to_string(s);
        }
    };

    class Hatring
    {
    public:
        std::string s;

        Pair p;

        [[nodiscard]] inline Hatring() noexcept = default;

        inline void operator=(const char& c)
        {
            p = c;
            s = c;
        }

        inline void operator+=(const char& c) noexcept
        {
            p += c;
            s.append(1ull, c);
        }

        [[nodiscard]] inline Hatring operator+(const std::string& other) const noexcept
        {
            Hatring h;
            h.s = s + other;
            h.p = p;
            for(const char& c : other)
                h.p += c;
            return h;
        }

        [[nodiscard]] inline bool operator==(const Pair& pp) const noexcept
        {
            return p == pp;
        }

        [[nodiscard]] inline bool operator!=(const Pair& pp) const noexcept
        {
            return p != pp;
        }

        inline void operator()() noexcept
        {
            p = Pair();
            s.clear();
        }
    };

    enum class FileType : u8
    {
        Iris,
        Sclera,
        Retina,
        Pupil,
        SystemLib,
        NativeLib,
        Unknown
    };

    class FileObject
    {
    public:
        std::string f;

        FileType ft = FileType::Iris;
    };

    class Using
    {
    public:
        Hatring h;

        u64 ln, ch;
    };

    using Module = std::string;

    enum class GlobalOperationMode : u8
    {
        Equal,
        EqualLiteral,

    };

    class GlobalOperation
    {
    public:
        Hatring field;

        u64 ln, ch;

        GlobalOperationMode gom;
    };

    class GlobalVariable
    {
    public:
        std::vector<GlobalOperation> ops;

        std::vector<Using> usings;

        std::vector<Module> modules;

        Hatring type, name;

        u64 typeln, typech, nameln, namech;

        bool initialized;

        inline void operator()() noexcept
        {
            ops.clear();
        }
    };

    bool NoReset = false;

    abool LogLock = false, ReadFileLock = false, GlobalVariablesLock = false;

    au64 MaxThreads;

    const std::string CompilerVersion("0.0.1");

    const std::string CompilerVersions[] = {"0.0.1"};

    constexpr Pair HashCompilerVersions[] = {Pair(11727686098800419294ull, 13502326805304175756ull)};

    std::string EyeFile, OutDir, LibsDir, SrcDir, DocsDir;

    //Clear on reset from here

    bool ExpatiatePlease = false;

    abool Proceed = true;

    Measurement MeasureUnit = Measurement::Microseconds;

    std::string Log, LogFile, ProjectName;

    Hatring ProjectCompilerVersion, ProjectVersion;

    std::vector<std::string> IgnoredFiles, FileIds;

    std::vector<GlobalVariable> GlobalVariables;

    inline void AddGlobalVariable(const GlobalVariable& gv) noexcept
    {
        while(GlobalVariablesLock);
        GlobalVariablesLock = true;
        GlobalVariables.push_back(gv);
        GlobalVariablesLock = false;
    }

    inline void ClearConsole() noexcept
    {
        #if defined(IrisWindows)
        std::system("cls");
        #else
        std::cout << "\033[2J\033[1;1H";
        #endif
    }

    [[nodiscard]] inline bool IsDirectory(const std::string& s) noexcept
    {
        return std::filesystem::is_directory(s);
    }

    [[nodiscard]] inline bool NewDirectory(const std::string& s) noexcept
    {
        return std::filesystem::create_directory(s);
    }

    [[nodiscard]] inline std::string GetDirectory(const std::string& s) noexcept
    {
        return s.substr(0, s.find_last_of("\\/")) + '/';
    }

    [[nodiscard]] inline std::vector<FileObject> GetFiles(const std::string& s, const FileType&& ft = FileType::Iris, const std::string&& ext = ".iris") noexcept
    {
        std::vector<FileObject> files;
        FileObject fo;
        fo.ft = ft;
        for(const auto& File : std::filesystem::recursive_directory_iterator(s))
		{
			fo.f = File.path().string();
            bool b = false;
            for(std::string ff : IgnoredFiles)
                if(fo.f == ff)
                {
                    b = true;
                    break;
                }
            if(!b && !std::filesystem::is_directory(fo.f))
            {
                u64 u = fo.f.size() - 1u;
                for(u64 uu = ext.size() - 1u; uu > 0u; --u, --uu)
                    if(fo.f[u] != ext[uu])
                    {
                        b = true;
                        break;
                    }
                if(!b && (fo.f[u] == ext[0u]))
                    files.push_back(fo);
            }
        }
        return files;
    }

    [[nodiscard]] inline bool IsFile(const std::string& s) noexcept
    {
        return !std::filesystem::is_directory(s) && std::filesystem::exists(s);
    }

    [[nodiscard]] inline const bool _DeleteFile(const std::string& s) noexcept
    {
        return std::filesystem::remove(s);
    }

    [[nodiscard]] inline const bool WriteFile(const std::string& s, const std::string& c) noexcept
    {
        if(IsFile(s))
            if(!_DeleteFile(s))
                return false;
        std::ofstream o(s);
        o << c;
        o.close();
        #if defined(EuraWindows)
        return std::filesystem::file_size(s) == (c.size() + std::count(c.begin(), c.end(), '\n'));
        #else
        return std::filesystem::file_size(s) == c.size();
        #endif
    }

    [[nodiscard]] inline std::string ReadFile(const std::string& s) noexcept
    {
        std::string c;
        c.reserve(std::filesystem::file_size(s));
        while(ReadFileLock);
        ReadFileLock = true;
        std::ifstream i(s);
        c.assign((std::istreambuf_iterator<char>(i)), std::istreambuf_iterator<char>());
        i.close();
        ReadFileLock = false;
        #if defined(IrisWindows)
        c.erase(std::remove(c.begin(), c.end(), '\r'), c.end());
        #endif
        return c;
    }

    [[nodiscard]] inline std::chrono::steady_clock::time_point Point() noexcept
    {
        return std::chrono::steady_clock::now();
    }

    [[nodiscard]] inline std::string TimeDiff(const std::chrono::steady_clock::time_point& a, const std::chrono::steady_clock::time_point& b) noexcept
    {
        if(MeasureUnit == Measurement::Nanoseconds)
			return std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count()) + " nanoseconds";
		else if(MeasureUnit == Measurement::Microseconds)
			return std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(b - a).count()) + " microseconds";
		return std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count()) + " milliseconds";
    }

    [[nodiscard]] inline std::string FormatSizeBytes(const f64 s) noexcept
    {
        if(s > 1024.)
        {
            f64 ss = s / 1024.;
            if(ss > 1024.)
            {
                ss /= 1024.;
                if(ss > 1024.)
                    return std::to_string(ss / 1024.) + " GiB";
                return std::to_string(ss) + " MiB";
            }
            return std::to_string(ss) + " KiB";
        }
        return std::to_string(static_cast<u64>(s)) + " bytes";
    }

    inline void ALog(const std::string& s) noexcept
    {
        while(LogLock);
        LogLock = true;
        Log += s;
        LogLock = false;
    }

    inline void LogHash(const std::string& s) noexcept
    {
        Pair p(s);
        Log += "\n\nword: " + s + ", first: " + p.First() + ", second: " + p.Second() + "\n\n";
    }

    //compilerversion
    constexpr Pair _CompilerVersion(10577848264423176554ull, 6151510658107240216ull);

    //name
    constexpr Pair Name(13709268971822177140ull, 14176396743819860870ull);

    //version
    constexpr Pair Version(14792314564648254299ull, 13502572527641750071ull);

    //pri
    constexpr Pair Private(15612225192418625972ull, 8646169223030243882ull);

    //measure
    constexpr Pair Measure(8809352708207431423ull, 13586824709325088415ull);

    //ns
    constexpr Pair Nanoseconds(590633490285535664ull, 626911876451167078ull);

    //mcs
    constexpr Pair Microseconds(15615038842674650332ull, 582730275372608502ull);

    //ms
    constexpr Pair Milliseconds(590634589797163781ull, 624114718869565969ull);

    //expatiate
    constexpr Pair Expatiate(13149114736251427534ull, 17497247821190643828ull);

    enum class Emode : u8
    {
        Global,
        PreComment,
        SingleLineComment,
        MultiLineComment,
        MultiLineEndComment,
        CompilerVersion,
        Name,
        Version,
        Measure,

    };

    namespace _0_0_1
    {
        enum class Imode : u8
        {
            Global,
            PreComment,
            SingleComment,
            MultiComment,
            MultiEndComment,
            GlobalTypeName,
            GlobalType,
            GlobalName,
            GlobalPostComma,
            GlobalOperationArgument,
            GlobalClassFieldInitializer,

        };

        inline void Iris(const std::string& f, const u64& ff) noexcept
        {
            const std::chrono::steady_clock::time_point a = Point();
            const std::string& content = ReadFile(f);
            std::vector<Using> usis;
            std::vector<Module> mods;
            GlobalVariable gv;
            GlobalOperation gop;
            Using usi;
            Hatring h;
            u64 ln = 1ull, ch = 0ull, lln, lch;
            Imode m = Imode::Global, lm;
            bool fc = false, id = false, on = false;
            const std::chrono::steady_clock::time_point b = Point();
            for(const char& c : content)
            {
                if(c == '\n')
                {
                    ++ln;
                    ch = 0ull;
                }
                else
                    ++ch;
                switch(m)
                {
                    case Imode::Global:
                        switch(c)
                        {
                            case IsNumeric:
                                if(!fc)
                                {
                                    Errori("the first character of a global variable type can't be numeric");
                                }
                                else
                                    h += c;
                            break;
                            case IsAlpha:
                                if(!fc)
                                {
                                    fc = true;
                                    lln = ln;
                                    lch = ch;
                                    h = c;
                                }
                                else
                                    h += c;
                            break;
                            case IsSpace:
                                if(fc)
                                {
                                    fc = false;
                                    if(h == Private)
                                    {

                                    }
                                    else
                                    {
                                        m = Imode::GlobalTypeName;
                                        gv.typeln = lln;
                                        gv.typech = lch;
                                        gv.modules = mods;
                                        gv.usings = usis;
                                    }
                                }
                            break;
                            case '.':
                                if(!fc)
                                {
                                    Errori("unexpected '.', expected the first character of the global variable type");
                                }
                                else
                                {
                                    fc = false;
                                    id = true;
                                    m = Imode::GlobalType;
                                    gv.typeln = lln;
                                    gv.typech = lch;
                                    h += '.';
                                    gv.modules = mods;
                                    gv.usings = usis;
                                }
                            break;
                            case '`':
                                lm = Imode::Global;
                                m = Imode::PreComment;
                            break;
                            default:
                                Errori("the character '" + std::string(1ull, c) + "' isn't alphanumeric");
                            break;
                        }
                    break;
                    case Imode::GlobalType:
                        switch(c)
                        {
                            case IsAlpha:
                                if(!fc)
                                {
                                    fc = true;
                                    id = false;
                                }
                                h += c;
                            break;
                            case IsNumeric:
                                if(!fc)
                                {
                                    Errori("the first character '" + std::string(1ull, c) + "' after '.' can't be numeric");
                                }
                                else
                                    h += c;
                            break;
                            case '.':
                                if(id)
                                {
                                    Errori("unexpected '.' after another '.'");
                                }
                                else
                                {
                                    id = true;
                                    fc = false;
                                    h += '.';
                                }
                            break;
                            case IsSpace:
                                if(fc)
                                {
                                    fc = false;
                                    m = Imode::GlobalTypeName;
                                }
                            break;
                            case '`':
                                lm = Imode::GlobalType;
                                m = Imode::PreComment;
                            break;
                            default:
                                Errori("non-alphanumeric character '" + std::string(1ull, c) + "'");
                            break;
                        }
                    break;
                    case Imode::GlobalName:
                        switch(c)
                        {
                            case IsAlphanumeric:
                                h += c;
                            break;
                            case ';':
                                m = Imode::Global;
                                gv.initialized = false;
                                gv.name = h;
                                AddGlobalVariable(gv);
                            break;
                            case ',':
                                m = Imode::GlobalPostComma;
                                gv.initialized = false;
                                gv.name = h;
                                AddGlobalVariable(gv);
                            break;
                            case '=':
                                m = Imode::GlobalOperationArgument;
                                gv.initialized = true;
                                gv.name = h;
                            break;
                            case IsSpace:
                            break;
                            case '`':
                                lm = Imode::GlobalName;
                                m = Imode::PreComment;
                            break;
                            default:
                                Errori("non-alphanumeric character '" + std::string(1ull, c) + "'");
                            break;
                        }
                    break;
                    case Imode::GlobalPostComma:
                        switch(c)
                        {
                            case IsAlpha:
                                m = Imode::GlobalName;
                                h = c;
                            break;
                            case IsSpace:
                            break;
                            case IsNumeric:
                                Errori("the first character '" + std::string(1ull, c) + "' of a global variable name can't be numeric");
                            break;
                            case '`':
                                lm = Imode::GlobalPostComma;
                                m = Imode::PreComment;
                            break;
                            default:
                                Errori("non-alpha character '" + std::string(1ull, c) + "'");
                            break;
                        }
                    break;
                    case Imode::GlobalTypeName:
                        switch(c)
                        {
                            case IsAlpha:
                                m = Imode::GlobalName;
                                gv.nameln = ln;
                                gv.namech = ch;
                                gv.type = h;
                                h = c;
                            break;
                            case '.':
                                if(id)
                                {
                                    Errori("unexpected '.' after other '.'");
                                }
                                else
                                {
                                    id = true;
                                    m = Imode::GlobalType;
                                    h += '.';
                                }
                            break;
                            case IsSpace:
                            break;
                            case '`':
                                lm = Imode::GlobalTypeName;
                                m = Imode::PreComment;
                            break;
                            case IsNumeric:
                                Errori("the first character of the global variable name '" + std::string(1ull, c) + "' can't be numeric");
                            break;
                            default:
                                Errori("the first character of the global variable name '" + std::string(1ull, c) + "' is non-alpha");
                            break;
                        }
                    break;
                    case Imode::GlobalOperationArgument:
                        switch(c)
                        {
                            case IsAlpha:
                                if(on)
                                {
                                    Errori("expected a numeric value, found '" + std::string(1ull, c) + "'");
                                }
                                else if(!fc)
                                {
                                    fc = true;
                                    gop.ln = ln;
                                    gop.ch = ch;
                                    h = c;
                                }
                                else
                                    h += c;
                            break;
                            case IsNumeric:
                                if(!fc)
                                {
                                    fc = true;
                                    on = true;
                                    gop.ln = ln;
                                    gop.ch = ch;
                                    h = c;
                                }
                                else
                                    h += c;
                            break;
                            case '.':
                                
                            break;
                            case ';':
                                if(!fc)
                                {
                                    Errori("unexpected ';' after '='");
                                }
                                else
                                {
                                    fc = false;
                                    m = Imode::Global;
                                    gop.gom = on ? GlobalOperationMode::EqualLiteral : GlobalOperationMode::Equal;
                                    on = false;
                                    gop.field = h;
                                    gv.ops.push_back(gop);
                                    AddGlobalVariable(gv);
                                    gv();
                                }
                            break;
                            case IsSpace:
                            break;
                            default:
                                Errori("the character '" + std::string(1ull, c) + "' of the global variable name is non-alphanumeric");
                            break;
                        }
                    break;
                    case Imode::PreComment:
                        switch(c)
                        {
                            case '`':
                                m = Imode::SingleComment;
                            break;
                            case '*':
                                m = Imode::MultiComment;
                            break;
                            default:
                                Errore("expected '`' or '*' after the comment initializer '`', found '" + std::string(1ull, c) + "'");
                            break;
                        }
                    break;
                    case Imode::SingleComment:
                        if(c == '\n')
                            m = lm;
                    break;
                    case Imode::MultiComment:
                        if(c == '*')
                            m = Imode::MultiEndComment;
                    break;
                    case Imode::MultiEndComment:
                        switch(c)
                        {
                            case '`':
                                m = lm;
                            break;
                            default:
                                m = Imode::MultiComment;
                            break;
                            case '*':
                            break;
                        }
                    break;
                }
            }
            if(m == Imode::SingleComment)
                m = lm;
            switch(m)
            {
                case Imode::Global:
                    if(!fc)
                    {
                        const std::chrono::steady_clock::time_point c = Point();
                        ALog("\n\nprocessing '" + FileIds[ff] + "' (" + FormatSizeBytes(content.size()) + ") took:\n\nreal(" + TimeDiff(a, c) + ")\nsys(" + TimeDiff(a, b) + ")\nuser(" + TimeDiff(b, c) + ")");
                    }
                    else
                    {
                        Errori("unexpected before the end of the file '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch));
                    }
                break;
                case Imode::GlobalOperationArgument:
                case Imode::GlobalName:
                    Errori("expected ';' before the end of the file to finish the global variable declaration with name '" + h.s + "' starting at " + std::to_string(gv.nameln) + " : " + std::to_string(gv.namech));
                break;
                case Imode::GlobalPostComma:
                    Errori("expected ';' instead of ',' before the end of the file to end the global variable declaration");
                break;
                case Imode::GlobalTypeName:
                case Imode::GlobalType:
                    Errori("expected the global variable name, and ';' to end the global variable declaration, after the global variable type '" + h.s + "' starting at " + std::to_string(gv.typeln) + " : " + std::to_string(gv.typech));
                break;
                case Imode::MultiComment:
                    Errori("expected '*`' to end the multi-line comment block");
                break;
                case Imode::MultiEndComment:
                    Errori("expected '`' to end the multi-line comment block");
                break;
                case Imode::PreComment:
                    Errori("unexpected comment initializer '`' at the end of the file");
                break;
            }
            goto epp;
            ep:;
            Proceed = false;
            epp:;
        }

        inline void Expatiating() noexcept
        {
            std::string o;
            for(const GlobalVariable& gv : GlobalVariables)
            {
                if(!gv.initialized)
                    o += "\n\nuninitialized ";
                else
                    o += "\n\ninitialized ";
                o += "global variable '" + gv.name.s + "' starting at " + std::to_string(gv.nameln) + " : " + std::to_string(gv.namech) + " with type '" + gv.type.s + "' starting at " + std::to_string(gv.typeln) + " : " + std::to_string(gv.typech);
                if(gv.initialized)
                {
                    o += " equals to ";
                    for(const GlobalOperation& go : gv.ops)
                        switch(go.gom)
                        {
                            case GlobalOperationMode::Equal:
                                o += "'" + go.field.s + "' starting at " + std::to_string(go.ln) + " : " + std::to_string(go.ch);
                            break;
                            case GlobalOperationMode::EqualLiteral:
                                o += "the literal '" + go.field.s + "' starting at " + std::to_string(go.ln) + " : " + std::to_string(go.ch);
                            break;
                        }
                }
            }
            Log += o;
        }
    }

    void Eye() noexcept
    {
        //LogHash("expatiate");
        //LogHash("ms");
        //LogHash("ns");
        std::vector<FileObject> Files;
        const std::chrono::steady_clock::time_point a = Point();
        const std::string& content = ReadFile(EyeFile);
        Hatring h;
        u64 ln = 1ull, ch = 0ull, lln, lch, aln, ach;
        Emode m = Emode::Global, lm;
        bool fc = false, ac = false;
        const std::chrono::steady_clock::time_point b = Point();
        for(const char& c : content)
        {
            switch(c)
            {
                default:
                    ++ch;
                break;
                case '\n':
                    ++ln;
                    ch = 0ull;
                break;
            }
            switch(m)
            {
                case Emode::Global:
                    switch(c)
                    {
                        case IsAlpha:
                            if(!fc)
                            {
                                fc = true;
                                lln = ln;
                                lch = ch;
                                h = c;
                            }
                            else
                                h += c;
                        break;
                        case IsSpace:
                            if(fc)
                            {
                                fc = false;
                                if(h == _CompilerVersion)
                                    m = Emode::CompilerVersion;
                                else if(h == Name)
                                    m = Emode::Name;
                                else if(h == Version)
                                    m = Emode::Version;
                                else if(h == Measure)
                                    m = Emode::Measure;
                                else if(h == Expatiate)
                                    ExpatiatePlease = true;
                                else
                                {
                                    Errore("unrecognized command '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch));
                                }
                            }
                        break;
                        case '`':
                            lm = Emode::Global;
                            m = Emode::PreComment;
                        break;
                        default:
                            if(!fc)
                            {
                                Errore("non-alpha first character '" + std::string(1ull, c) + "'");
                            }
                            else
                            {
                                Errore("non-alpha character '" + std::string(1ull, c) + "' after the command '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch));
                            }
                        break;
                    }
                break;
                case Emode::CompilerVersion:
                    switch(c)
                    {
                        case IsNumeric:
                            if(!fc)
                            {
                                fc = true;
                                lln = ln;
                                lch = ch;
                                if(!ac)
                                    h = c;
                                else
                                    h += c;
                            }
                            else
                                h += c;
                        break;
                        case IsSpace:
                            if(fc)
                            {
                                m = Emode::Global;
                                for(const Pair& p : HashCompilerVersions)
                                    if(h == p)
                                    {
                                        fc = false;
                                        ac = false;
                                        ProjectCompilerVersion = h;
                                        break;
                                    }
                                if(fc)
                                {
                                    if(!ac)
                                    {
                                        Errore("the compiler version '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch) + ", doesn't exists");
                                    }
                                    else
                                    {
                                        Errore("the compiler version '" + h.s + "' starting at " + std::to_string(aln) + " : " + std::to_string(ach) + ", doesn't exists");
                                    }
                                }
                            }
                        break;
                        case '.':
                            if(!fc)
                            {
                                if(!ac)
                                {
                                    Errore("empty compiler version before '.'");
                                }
                                else
                                {
                                    Errore("empty compiler sub-version before '.' and after '" + h.s + "' starting at " + std::to_string(aln) + " : " + std::to_string(ach));
                                }
                            }
                            else if(!ac)
                            {
                                fc = false;
                                ac = true;
                                aln = lln;
                                ach = lch;
                                h += '.';
                            }
                            else
                            {
                                fc = false;
                                h += '.';
                            }
                        break;
                        case '`':
                            lm = Emode::CompilerVersion;
                            m = Emode::PreComment;
                        break;
                        default:
                            Errore("non-numeric character '" + std::string(1ull, c) + "'");
                        break;
                    }
                break;
                case Emode::Name:
                    switch(c)
                    {
                        case IsAlpha:
                            if(!fc)
                            {
                                fc = true;
                                h.s = c;
                            }
                            else
                                h.s.append(1ull, c);
                        break;
                        case IsNumeric:
                            if(!fc)
                            {
                                Errore("the first character of the project name '" + std::string(1ull, c) + "', cannot be numeric");
                            }
                            else
                                h.s.append(1ull, c);
                        break;
                        case IsSpace:
                            if(fc)
                            {
                                fc = false;
                                m = Emode::Global;
                                ProjectName = h.s;
                            }
                        break;
                        case '`':
                            lm = Emode::Name;
                            m = Emode::PreComment;
                        break;
                        default:
                            Errore("non-alphanumeric character '" + std::string(1ull, c) + "'");
                        break;
                    }
                break;
                case Emode::Version:
                    switch(c)
                    {
                        case IsNumeric:
                            if(!fc)
                            {
                                fc = true;
                                lln = ln;
                                lch = ch;
                                if(!ac)
                                    h = c;
                                else
                                    h += c;
                            }
                            else
                                h += c;
                        break;
                        case IsSpace:
                            if(fc)
                            {
                                fc = false;
                                ac = false;
                                m = Emode::Global;
                                ProjectVersion = h;
                            }
                        break;
                        case '.':
                            if(!fc)
                            {
                                if(!ac)
                                {
                                    Errore("empty project version before '.'");
                                }
                                else
                                {
                                    Errore("empty project sub-version before '.' and after '" + h.s + "' starting at " + std::to_string(aln) + " : " + std::to_string(ach));
                                }
                            }
                            else if(!ac)
                            {
                                fc = false;
                                ac = true;
                                aln = lln;
                                ach = lch;
                                h += '.';
                            }
                            else
                            {
                                fc = false;
                                h += '.';
                            }
                        break;
                        case '`':
                            lm = Emode::Version;
                            m = Emode::PreComment;
                        break;
                        default:
                            Errore("non-numeric character '" + std::string(1ull, c) + "'");
                        break;
                    }
                break;
                case Emode::Measure:
                    switch(c)
                    {
                        case IsAlpha:
                            if(!fc)
                            {
                                fc = true;
                                lln = ln;
                                lch = ch;
                                h = c;
                            }
                            else
                                h += c;
                        break;
                        case IsSpace:
                            if(fc)
                            {
                                fc = false;
                                m = Emode::Global;
                                if(h == Nanoseconds)
                                    MeasureUnit = Measurement::Nanoseconds;
                                else if(h == Milliseconds)
                                    MeasureUnit = Measurement::Milliseconds;
                                else if(h != Microseconds)
                                {
                                    Errore("unrecognized measurement unit '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch) + ", expected 'ms', 'mcs' or 'ns'");
                                }
                            }
                        break;
                        case '`':
                            lm = Emode::Measure;
                            m = Emode::PreComment;
                        break;
                        default:
                            Errore("non-alpha character '" + std::string(1ull, c) + "'");
                        break;
                    }
                break;
                case Emode::SingleLineComment:
                    if(c == '\n')
                        m = lm;
                break;
                case Emode::MultiLineComment:
                    if(c == '*')
                        m = Emode::MultiLineEndComment;
                break;
                case Emode::PreComment:
                    switch(c)
                    {
                        case '`':
                            m = Emode::SingleLineComment;
                        break;
                        case '*':
                            m = Emode::MultiLineComment;
                        break;
                        default:
                            Errore("expected '`' or '*' after the comment initializer '`', found '" + std::string(1ull, c) + "'");
                        break;
                    }
                break;
                case Emode::MultiLineEndComment:
                    switch(c)
                    {
                        case '`':
                            m = lm;
                        break;
                        default:
                            m = Emode::MultiLineComment;
                        break;
                        case '*':
                        break;
                    }
                break;
            }
        }
        if(m == Emode::SingleLineComment)
            m = lm;
        switch(m)
        {
            case Emode::Global:
                if(fc)
                {
                    if(h == Expatiate)
                        ExpatiatePlease = true;
                    else
                    {
                        Errore("unrecognized command '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch));
                    }
                }
            break;
            case Emode::CompilerVersion:
                if(!fc)
                {
                    if(!ac)
                    {
                        Errore("empty compiler version");
                    }
                    else
                    {
                        Errore("empty compiler sub-version after '" + h.s + "' starting at " + std::to_string(aln) + " : " + std::to_string(ach));
                    }
                }
                else
                {
                    for(const Pair& p : HashCompilerVersions)
                        if(h == p)
                        {
                            fc = false;
                            ProjectCompilerVersion = h;
                            break;
                        }
                    if(fc)
                    {
                        if(!ac)
                        {
                            Errore("the compiler version '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch) + ", doesn't exists");
                        }
                        else
                        {
                            Errore("the compiler version '" + h.s + "' starting at " + std::to_string(aln) + " : " + std::to_string(ach) + ", doesn't exists");
                        }
                    }
                }
            break;
            case Emode::Name:
                if(!fc)
                {
                    Errore("empty project name");
                }
                else
                    ProjectName = h.s;
            break;
            case Emode::Version:
                if(!fc)
                {
                    if(!ac)
                    {
                        Errore("empty project version");
                    }
                    else
                    {
                        Errore("empty project sub-version after '" + h.s + "' starting at " + std::to_string(aln) + " : " + std::to_string(ach));
                    }
                }
                else
                    ProjectVersion = h;
            break;
            case Emode::Measure:
                if(fc)
                {
                    if(h == Nanoseconds)
                        MeasureUnit = Measurement::Nanoseconds;
                    else if(h == Milliseconds)
                        MeasureUnit = Measurement::Milliseconds;
                    else if(h != Microseconds)
                    {
                        Errore("expected 'ns', 'ms' or 'mcs' as measurement unit, found '" + h.s + "' starting at " + std::to_string(lln) + " : " + std::to_string(lch));
                    }
                }
                else
                {
                    Errore("expected a measurement unit");
                }
            break;
            case Emode::MultiLineComment:
                Errore("expected '*`' to end the multi-line comment block");
            break;
            case Emode::MultiLineEndComment:
                Errore("expected '`' to end the multi-line comment block");
            break;
            case Emode::PreComment:
                Errore("expected '`' or '*' after the comment initializer '`'");
            break;
        }
        {
            const std::chrono::steady_clock::time_point c = Point();
            ALog("\n\nprocessing '" + EyeFile + "' (" + FormatSizeBytes(content.size()) + ") took:\n\nreal(" + TimeDiff(a, c) + ")\nsys(" + TimeDiff(a, b) + ")\nuser(" + TimeDiff(b, c) + ")");
        }
        //0.0.1
        if(ProjectCompilerVersion == HashCompilerVersions[0ull])
        {
            bool boo;
            {
                std::vector<FileObject> IrisFiles = GetFiles(SrcDir);
                Files.insert(std::end(Files), std::begin(IrisFiles), std::end(IrisFiles));
                boo = IrisFiles.empty();
            }
            if(boo)
                ALog("\n\nerror at '" + SrcDir + "' -> no '.iris' files");
            else
            {
                {
                    std::vector<FileObject> PupilFiles = GetFiles(DocsDir, FileType::Pupil, ".pupil");
                    std::vector<FileObject> RetinaFiles = GetFiles(LibsDir, FileType::Retina, ".retina");
                    std::vector<FileObject> ScleraFiles = GetFiles(SrcDir, FileType::Sclera, ".sclera");
                    Files.insert(std::end(Files), std::begin(RetinaFiles), std::end(RetinaFiles));
                    Files.insert(std::end(Files), std::begin(PupilFiles), std::end(PupilFiles));
                    Files.insert(std::end(Files), std::begin(ScleraFiles), std::end(ScleraFiles));
                }
                std::vector<std::thread> threads;
                std::string xxxxxx;
                u64 x = 0ull, xx = 1ull, xxxxxxx;
                const u64 xxx = Files.size(), xxxx = MaxThreads;
                threads.reserve(xxx);
                if(xxxx == 1ull)
                    while(x < xxx)
                    {
                        xxxxxxx = x;
                        std::string& xxxxx = Files[x].f;
                        xxxxxx = xxxxx;
                        xxxxxx.erase(0ull, SrcDir.size());
                        FileIds.push_back(xxxxxx);
                        switch(Files[x++].ft)
                        {
                            case FileType::Iris:
                                _0_0_1::Iris(xxxxx, xxxxxxx);
                            break;
                            default:
                            break;
                        }
                    }
                else
                    while(x < xxx)
                        while(x < xxx && xx < xxxx)
                        {
                            xxxxxxx = x;
                            std::string& xxxxx = Files[x].f;
                            xxxxxx = xxxxx;
                            xxxxxx.erase(0ull, SrcDir.size());
                            FileIds.push_back(xxxxxx);
                            switch(Files[x++].ft)
                            {
                                case FileType::Iris:
                                    ++xx;
                                    threads.push_back(std::thread([&xxxxx, &xx, &xxxxxxx]()
                                    {
                                        _0_0_1::Iris(xxxxx, xxxxxxx);
                                        --xx;
                                    }));
                                break;
                                default:
                                break;
                            }
                        }
                for(auto& th : threads)
                    th.join();
                if(Proceed)
                {
                    if(ExpatiatePlease)
                        _0_0_1::Expatiating();
                }
            }
        }
        ep:;
    }

    [[noreturn]] inline void Compile() noexcept;

    inline void Reset() noexcept
    {
        if(NoReset)
        {
            if(!WriteFile(LogFile, Log))
            {
                std::cout << "the log message couldn't be exported to '" << LogFile << "'\n\npress 'r' to recompile or any other key to exit, and 'enter'..." << std::endl;
                char c;
                std::cin >> c;
            }
        }
        else if(!LogFile.empty())
        {
            if(WriteFile(LogFile, Log))
                std::cout << "the log message was exported to '" << LogFile << "'\n\npress 'r' to recompile or any other key to exit, and 'enter'..." << std::endl;
            else
                std::cout << "the log message couldn't be exported to '" << LogFile << "'" << std::endl;
        }
        if(!NoReset)
        {
            if(LogFile.empty())
                std::cout << Log << "\n\npress 'r' to recompile or any other key to exit, and 'enter'..." << std::endl;
            Proceed = true;
            ExpatiatePlease = false;
            MeasureUnit = Measurement::Microseconds;
            LogFile.clear();
            Log.clear();
            IgnoredFiles.clear();
            FileIds.clear();
            GlobalVariables.clear();
            char c;
            std::cin >> c;
            if(c == 'r')
                Compile();
        }
    }

    const char* help_msg = "\n\nuse 'help' command to get the list of available commands";

    inline void panic_msg()
    {
        std::cout << "\n\npress any key and 'enter' to exit...\n";
        char c;
        std::cin >> c;
    }

    [[noreturn]] inline void Compile() noexcept
    {
        ClearConsole();
        if(!IsFile(EyeFile))
        {
            std::cout << "The project file '" << EyeFile << "' doesn't exists";
            panic_msg();
        }
        else if(!IsDirectory(SrcDir))
        {
            std::cout << "The project source directory '" << SrcDir << "' doesn't exists";
            panic_msg();
        }
        else if(!IsDirectory(LibsDir))
        {
            std::cout << "The project libraries directory '" << LibsDir << "' doesn't exists";
            panic_msg();
        }
        else if(!IsDirectory(OutDir))
        {
            std::cout << "The project output directory '" << OutDir << "' doesn't exists";
            panic_msg();
        }
        else if(!IsDirectory(DocsDir))
        {
            std::cout << "The project documentation directory '" << DocsDir << "' doesn't exists";
            panic_msg();
        }
        else
        {
            ProjectVersion.s = CompilerVersions[0ull];
            ProjectVersion.p = HashCompilerVersions[0ull];
            ProjectCompilerVersion.s = CompilerVersions[0ull];
            ProjectCompilerVersion.p = HashCompilerVersions[0ull];
            ProjectName = "Project";
            Eye();
            Reset();
        }
    }

    inline void Process(int argc, char* argv[]) noexcept
    {
        ClearConsole();
        if(argc == 2)
        {
            std::string a(argv[1]);
            if(a == "version")
                std::cout << "iris version: " << CompilerVersion;
            else if(a == "help")
                std::cout << "iris help:\n\n\t[cmd] - [description]\n\n\tversion - get the compiler version\n\n\tcreate project_location project_name - creates a new iris project where project_name is the name of the project(if there's already a project with that name on the same location, the creation will fail without touching your existent project) and project_location is the base directory of the project(will create a new one if it doesn't exists)\n\n\tcompile eye_file - compiles the project specified on eye_file(this should be an existent '.eye' valid project file)";
            else
                std::cout << "unknown command '" << a << "'" << help_msg;
            panic_msg();
        }
        else if(argc == 4)
        {
            std::string a(argv[1]), b(argv[2]), c(b + '/' + argv[3]), d(c + '/' + argv[3] + ".eye"), e(c + "/src"), f(c + "/libs"), g(c + "/out"), h(c + "/docs");
            if(a == "create")
            {
                bool bb = false;
                if(!IsDirectory(b))
                {
                    if(b.size() > 3ull)
                    {
                        std::string lel;
                        for(u64 x = 0ull; x < b.size(); ++x)
                        {
                            const char& c = b[x];
                            if(c == '\\' || c == '/')
                                if(!IsDirectory(lel))
                                    if(!NewDirectory(lel))
                                    {
                                        bb = true;
                                        break;
                                    }
                            lel.append(1ull, c);
                            if(x == (b.size() - 1ull))
                                if(!IsDirectory(lel))
                                    if(!NewDirectory(lel))
                                    {
                                        bb = true;
                                        break;
                                    }
                        }
                    }
                    else
                        bb = true;
                }
                if(!bb)
                {
                    if(IsDirectory(c))
                        std::cout << "\n\nthe project directory '" << c << "' already exists";
                    else if(NewDirectory(c))
                    {
                        std::cout << "\n\nthe project directory '" << c << "' were successfully created";
                        bool bbbbbb = true;
                        bbbbbb = NewDirectory(e);
                        bbbbbb = NewDirectory(f);
                        bbbbbb = NewDirectory(g);
                        bbbbbb = NewDirectory(h);
                        bbbbbb = WriteFile(d, std::string("compilerversion " + CompilerVersion + "\nname " + argv[3] + "\nversion "));
                        if(!bbbbbb || bbbbbb)
                            std::cout << "\n\nthe project were successfully created";
                    }
                }
                else
                    std::cout << "the project base folder '" << b << "' couldn't be created";
            }
            else
                std::cout << "unknown command '" << a << "'" << help_msg;
            panic_msg();
        }
        else if(argc == 3)
        {
            if(std::string(argv[1]) == "compile")
            {
                if(IsFile(std::string(argv[2])))
                {
                    EyeFile = argv[2];
                    SrcDir = GetDirectory(argv[2]) + "src/";
                    OutDir = GetDirectory(argv[2]) + "out/";
                    LibsDir = GetDirectory(argv[2]) + "libs/";
                    DocsDir = GetDirectory(argv[2]) + "docs/";
                    MaxThreads = std::thread::hardware_concurrency();
                    if(MaxThreads < 2ull)
                    {
                        std::cout << "error on the number of physical threads(or cores), you need to have at least 2";
                        panic_msg();
                    }
                    else
                        Compile();
                }
                else
                    std::cout << "the project file to compile '" << argv[2] << "' doesn't exists" << help_msg;
            }
            else
            {
                std::cout << "unknown command '" << argv[1] << "'" << help_msg;
                panic_msg();
            }
        }
        else
        {
            std::cout << "invalid number of arguments" << help_msg;
            panic_msg();
        }
    }
}

int main(int argc, char* argv[])
{
    Iris::Process(argc, argv);
    return 0;
}