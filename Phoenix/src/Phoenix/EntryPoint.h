//
//  EntryPoint.h
//  Phoenix
//
//  Created by SD on 09/10/20.
//  Copyright © 2020 LinuxSDA. All rights reserved.
//

#ifndef EntryPoint_h
#define EntryPoint_h

extern std::unique_ptr<Phoenix::Application> Phoenix::CreateApplication();

int main()
{
    std::cout << "Phoenix Engine!" << std::endl;
    auto application = Phoenix::CreateApplication();
    application->Run();
}
#endif /* EntryPoint_h */
