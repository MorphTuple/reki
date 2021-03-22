#include <sleepy_discord/sleepy_discord.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

class Command{
    public : virtual std::string getName() = 0;
    public : virtual void exec(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) = 0;
};

class Ping : public Command{
    public : std::string getName() override{
        return "ping";
    }
    
    public : void exec(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override{
        client->sendMessage(message.channelID, "Hello");
    }   
};

class About : public Command{
    public : std::string getName() override{
        return "about";
    }

    public : void exec(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override{
        auto embed = SleepyDiscord::Embed();
        embed.author.name = "Reki Kyan from SK8 the Infinity";
        embed.author.iconUrl = "https://nyaa.shikimori.one/system/characters/original/188060.jpg?1612740482";
        embed.description = "Reki Kyan is a character from the anime SK8 the Infinity. It is meant for practicing C++ and also just for fun. Built with sleepy-discord and C++ programming language.\n\nReki version 1.0 was made and developed by:\n**???**\nReki Bot is licensed under GNU GPLv3:\n(https://www.gnu.org/licenses/gpl-3.0.en.html)[https://www.gnu.org/licenses/gpl-3.0.en.html]";
        embed.thumbnail.url = "https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fimg.icons8.com%2Fcolor%2F1600%2Fc-plus-plus-logo.png&f=1&nofb=1";
        embed.color = 0xff4d4d;

        client->sendMessage(message.channelID, "", embed);
    }
};

class CountBots : public Command{
    public : std::string getName() override{
        return "countbots";
    }

    public : void exec(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override{
        if(message.serverID.empty()){
            client->sendMessage(message.channelID, "You need to be in a server to run this");
            return;
        }
        
        auto members = client->listMembers(message.serverID, 100);
        auto membersList = members.list();

        int bots = 0;
        int humans = 0;

        for(auto const& it : membersList){
            if(it.user.bot){
                bots++;
                std::cout << "Bots " << bots;
            } else {
                humans++;
                std::cout << "Humans " << humans;
            }
        }

        std::ostringstream msg;
        msg << "Humans: " << humans << "\nBots: " << bots;
        client->sendMessage(message.channelID, msg.str());
    }
};