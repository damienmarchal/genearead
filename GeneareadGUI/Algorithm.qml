import QtQuick 2.0

Item {
    function call(arguments) {
        console.log("Got message:", arguments)
        return arguments.length==0 ? "Nothing" : "Something"
    }
}


