//
//  Instrumentor.h
//  Phoenix
//
//  Created by SD on 29/12/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#pragma once

namespace Phoenix
{
    struct ProfileResult
    {
        const char* Name;
        uint64_t Start, End;
        size_t ThreadID;
    };
    
    /* TODO: Not thread safe*/
    
    class Instrumentor
    {
    public:
        Instrumentor() : m_ProfileCount(0)
        {
        }
        
        void BeginSession(const std::string& filepath = "results.json")
        {
            m_OutputStream.open(filepath);
            WriteHeader();
        }
        
        void EndSession()
        {
            WriteFooter();
            m_OutputStream.close();
            m_ProfileCount = 0;
        }
        
        void WriteProfile(const ProfileResult& result)
        {
            if (m_ProfileCount++ > 0)
                m_OutputStream << ",";
            
            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            m_OutputStream << "\"name\":\"" << result.Name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start;
            m_OutputStream << "}";
            
            m_OutputStream.flush();
        }
        
        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }
        
    private:
        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }
        
        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }
        
    private:
        std::ofstream   m_OutputStream;
        int             m_ProfileCount;
    };
    
    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name): m_Name(name)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }
        
        ~InstrumentationTimer()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();
            
            uint64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            uint64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
            
            size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });
        }
        
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    };
    
}

#if PX_PROFILE_PERFORMANCE
    #define PX_PROFILE_BEGIN_SESSION(filepath) ::Phoenix::Instrumentor::Get().BeginSession(filepath)
    #define PX_PROFILE_END_SESSION() ::Phoenix::Instrumentor::Get().EndSession()
    #define PX_PROFILE_SCOPE(name) ::Phoenix::InstrumentationTimer timer##__LINE__(name);
    #define PX_PROFILE_FUNCTION() PX_PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
    #define PX_PROFILE_BEGIN_SESSION(filepath)
    #define PX_PROFILE_END_SESSION()
    #define PX_PROFILE_SCOPE(name)
    #define PX_PROFILE_FUNCTION()
#endif
