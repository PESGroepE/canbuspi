#ifndef CANBUSPI_EVENT_H
#define CANBUSPI_EVENT_H

#include <string>

/**
 * @brief Enum met event types.
 */
enum Type {
    NONE,
    HUMIDITY,
    BRAND,
    SLUISKNOP,
    NOODKNOP
};

/**
 * @brief Event klasse waarmee gebeurtenissen kunnen worden uitgewisseld tussen systemen.
 */
class Event {
public:
    /**
    * Construeer een nieuw Event object.
    * @brief Constructor.
    */
    Event();

    /**
    * Construeer een nieuw Event object met parameters.
    * @brief Constructor.
    * @param type Type event uit de enum.
    * @param data Data die in het event moet staan.
    */
    Event(Type, std::string);

    /**
    * @brief Vraag het type van het event op.
    */
    Type getType() const;

    /**
    * @brief Vraag de data van het event op.
    */
    std::string getData() const;

    /**
    * @brief Stel het type van het event in.
    */
    void setType(Type);

    /**
    * @brief Stel de data van het event in.
    */
    void setData(std::string);

private:
    /**
    * @brief Stel het type van het event in.
    */
    Type type;

    /**
    * @brief Stel het type van het event in.
    */
    std::string data;
};


#endif //CANBUSPI_EVENT_H
