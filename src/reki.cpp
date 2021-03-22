#include <iostream>
#include <sleepy_discord/sleepy_discord.h>
#include <algorithm>
#include "commands/command.cpp"

class Reki : public SleepyDiscord::DiscordClient{
    private : std::map<std::string, std::unique_ptr<Command>> cmds;
    private : std::string prefix;

    public : Reki(std::string token, std::string newPrefix = "r!") : SleepyDiscord::DiscordClient(token) {
        prefix = newPrefix;
        cmds["ping"] = std::make_unique<Ping>();
        cmds["about"] = std::make_unique<About>();
        cmds["countbots"] = std::make_unique<CountBots>();

        std::cout << "Prefix is " << prefix << "\n";
    }

    void onMessage(SleepyDiscord::Message message) override{
        std::cout << message.content;
        if(message.author.bot) return;

        std::string c = message.content;
        std::transform(c.begin(), c.end(), c.begin(), [](unsigned char c){ return std::tolower(c); });

        if(c.rfind(prefix, 0) != 0) return;
        std::string requestedCmd = c.erase(0, prefix.length());

        if(cmds.count(requestedCmd)){
            cmds[requestedCmd]->exec(this, message);
        }
    }
};

int main(){
    std::cout << "//Reki\n";

    char* token = getenv("TOKEN");
    char* prefix = getenv("PREFIX");

    if (token == NULL){
        std::cerr << "Token not found\n";
        return 0;
    }

    Reki r(token, prefix);

    r.run();

    return 0;
}