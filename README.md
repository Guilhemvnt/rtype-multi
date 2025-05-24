# R-Type

Latest project of the third year at EPITECH in `C++`.

---
## Availability

Our project is available for `macOS`, `Linux` and `Windows` platforms.

---
## Documentation

The documentation of the project is available in the Wiki section.

A very detailled developer documentation is available in the [Documentation/html](Documentation/html) folder **ONLY** if `doxygen` has been run before.

---
## Release

Releases of the project are actually available [here](https://github.com/EpitechPromo2026/B-CPP-500-LYN-5-2-rtype-erwann.laplante/releases).

Select your platform and download the archive, then extract it using the following command:

```bash
tar -xzf r-type-[version]-[platform].tar.gz
```

Then you can launch the server and the client using the commands from above.

## Diagram of the project
```mermaid
flowchart TD
    %% Client Application Layer
    subgraph "Client Application"
        direction TB
        subgraph "Engine (Game Loop)"
            direction TB
            E1["Engine:\nEntityManager, EntityFactory\nSystems:\nInput, AI, Mvt,\nCollision, Powerup"]:::gameLogic
        end
        subgraph "Rendering/UI (Graph)"
            direction TB
            G1["Graph:\nObjectManager, ObjectFactory,\nScene, AudioManager,\nButton/UI"]:::rendering
        end
        subgraph "Networking (ClientConnection)"
            direction TB
            N1["ClientConnection"]:::networking
        end
        subgraph "OS Signal Handling (CtrlC)"
            direction TB
            O1["CtrlC"]:::util
        end
    end

    %% Server Application Layer
    subgraph "Server Application"
        direction TB
        subgraph "Networking & Lobby"
            direction TB
            N2["Server & Lobby"]:::networking
        end
        subgraph "Game State Manager"
            direction TB
            S1["Authoritative Game State\n(ECS modules"]:::gameLogic
        end
        subgraph "Score Persistence"
            direction TB
            SP["infScore.txt\nlevelScore.txt"]:::data
        end
    end

    %% Shared Utilities
    subgraph "Shared Utilities"
        direction TB
        JP["JSON Parser"]:::util
        EH["Error Handling"]:::util
    end

    %% Build & Scripts
    subgraph "Build & Install Scripts"
        direction TB
        B1["CMakeLists.txt\nscripts/*"]:::build
    end

    %% Config Files
    CFG["Config Files:\nEntityConfig.json,\nLevelConfig.json,\nAssetsConfig.json,\nGameConfig.json"]:::data

    %% Relationships
    CFG -->|loads config| JP
    JP -->|provides data| E1
    JP -->|provides data| G1
    E1 -->|"game state snapshots"| G1
    O1 -.->|interrupt signal| E1
    N1 <-->|user input events| N2
    N2 -->|"state update"| S1
    S1 -->|"state packets"| N2
    S1 -.->|persist scores| SP
    B1 --> E1
    B1 --> G1
    B1 --> N1
    B1 --> N2
    B1 --> JP
    B1 --> EH

    %% Click Events
    click E1 "https://github.com/guilhemvnt/rtype-multi/tree/main/include/Engine"
    click E1 "https://github.com/guilhemvnt/rtype-multi/tree/main/include/Engine/Components"
    click E1 "https://github.com/guilhemvnt/rtype-multi/tree/main/include/Engine/Entities"
    click E1 "https://github.com/guilhemvnt/rtype-multi/tree/main/include/Engine/Systems"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Engine.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Entities/Entity.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Entities/EntityFactory.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Entities/EntityManager.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Systems/AISystem.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Systems/CollisionSystem.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Systems/InputSystem.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Systems/MvtSystem.cpp"
    click E1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/Systems/PowerupSystem.cpp"
    click CFG "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/EntityConfig.json"
    click CFG "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Engine/LevelConfig.json"

    click G1 "https://github.com/guilhemvnt/rtype-multi/tree/main/include/Graph"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/AudioFactory.cpp"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/AudioManager.cpp"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/Button.cpp"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/Game.cpp"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/GameObject.cpp"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/InputButton.cpp"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/ObjectFactory.cpp"
    click G1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/ObjectManager.cpp"
    click CFG "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/AssetsConfig.json"
    click CFG "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Graph/GameConfig.json"

    click N1 "https://github.com/guilhemvnt/rtype-multi/blob/main/include/Client/Client.hpp"
    click N1 "https://github.com/guilhemvnt/rtype-multi/blob/main/include/Client/ClientConnection.hpp"
    click N1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Client/ClientConnection.cpp"
    click N1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Client/main.cpp"

    click O1 "https://github.com/guilhemvnt/rtype-multi/blob/main/include/CtrlC/CtrlC.hpp"
    click O1 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/CtrlC/CtrlC.cpp"

    click N2 "https://github.com/guilhemvnt/rtype-multi/blob/main/include/Server/Lobby.hpp"
    click N2 "https://github.com/guilhemvnt/rtype-multi/blob/main/include/Server/Server.hpp"
    click N2 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Server/main.cpp"
    click N2 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Server/server.cpp"
    click N2 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Server/lobby.cpp"
    click N2 "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Server/Handle.cpp"

    click SP "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Server/scores/infScore.txt"
    click SP "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Server/scores/levelScore.txt"

    click JP "https://github.com/guilhemvnt/rtype-multi/blob/main/include/JsonParser/JsonParser.hpp"
    click JP "https://github.com/guilhemvnt/rtype-multi/blob/main/src/JsonParser/JsonParser.cpp"

    click EH "https://github.com/guilhemvnt/rtype-multi/blob/main/include/Error/Error.hpp"
    click EH "https://github.com/guilhemvnt/rtype-multi/blob/main/src/Error/Error.cpp"

    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/CMakeLists.txt"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/linux/build.sh"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/linux/install.sh"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/macos/build.sh"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/macos/install.sh"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/windows/build.bat"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/windows/install.bat"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/utils/test_coverage.sh"
    click B1 "https://github.com/guilhemvnt/rtype-multi/blob/main/scripts/utils/update_current_branches.sh"

    %% Styles
    classDef gameLogic fill:#AED6F1,stroke:#1F618D,color:#1B4F72;
    classDef rendering fill:#A9DFBF,stroke:#196F3D,color:#145A32;
    classDef networking fill:#F9E79F,stroke:#B7950B,color:#7D6608;
    classDef data fill:#D7BDE2,stroke:#784212,color:#512E5F;
    classDef util fill:#E5E8E8,stroke:#566573,color:#2C3E50;
    classDef build fill:#EDBB99,stroke:#A04000,color:#641E16;
```

---
## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for more details.
