# Command list

## Server

### As Unauthorised User
- **AUTH** [username] [password] - *Register as new user*
- **LOGIN** [username] [password] - *Login with existing account*
- **QUIT** - *Close connection*

### As Authorised User
- **SEND** [message] - *Send message to all availible user*

### As Moderator only
- **SET** [username] [number] [message] - *Moderate messages*
- **FAULT** - *Get fault list*

## User
- **ERR** [message] - *Error message*
- **INF** [message] - *Informational message*
- **EDI** [username] : [message] - *To main moder to edit messages*
- **MSG** [message] - *Message from users*
- **FREZ** [[username] [number]] - *Fault list send*
