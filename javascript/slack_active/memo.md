# slack であるユーザーがactiveになったら通知するやつ

# 使うAPI

### users.getPresence
* https://api.slack.com/methods/users.getPresence

satomin https://slack.com/api/users.getPresence?token=xoxp-10122799667-10122799683-17082740341-0e4690e12c&user=U0A3QEMNW&pretty=1

yorisilo https://slack.com/api/users.getPresence?token=xoxp-10122799667-10122799683-17082740341-0e4690e12c&user=U0A3LPHL3&pretty=1

### users.list
* https://api.slack.com/methods/users.list

https://slack.com/api/users.list?token=xoxp-10122799667-10122799683-17082740341-0e4690e12c&presence=1&pretty=1

## satomin
 {
            "id": "U0A3QEMNW",
            "team_id": "T0A3LPHKM",
            "name": "satomin0209",
            "deleted": false,
            "status": null,
            "color": "4bbe2e",
            "real_name": "",
            "tz": "Asia\/Tokyo",
            "tz_label": "Japan Standard Time",
            "tz_offset": 32400,
            "profile": {
                "avatar_hash": "g6fdedec5517",
                "real_name": "",
                "real_name_normalized": "",
                "email": "satomine0209@gmail.com",
                "image_24": "https:\/\/secure.gravatar.com\/avatar\/6fdedec551753aee3ca80c295794a088.jpg?s=24&d=https%3A%2F%2Fa.slack-edge.com%2F66f9%2Fimg%2Favatars%2Fava_0006-24.png",
                "image_32": "https:\/\/secure.gravatar.com\/avatar\/6fdedec551753aee3ca80c295794a088.jpg?s=32&d=https%3A%2F%2Fa.slack-edge.com%2F66f9%2Fimg%2Favatars%2Fava_0006-32.png",
                "image_48": "https:\/\/secure.gravatar.com\/avatar\/6fdedec551753aee3ca80c295794a088.jpg?s=48&d=https%3A%2F%2Fa.slack-edge.com%2F66f9%2Fimg%2Favatars%2Fava_0006-48.png",
                "image_72": "https:\/\/secure.gravatar.com\/avatar\/6fdedec551753aee3ca80c295794a088.jpg?s=72&d=https%3A%2F%2Fa.slack-edge.com%2F66f9%2Fimg%2Favatars%2Fava_0006-72.png",
                "image_192": "https:\/\/secure.gravatar.com\/avatar\/6fdedec551753aee3ca80c295794a088.jpg?s=192&d=https%3A%2F%2Fa.slack-edge.com%2F7fa9%2Fimg%2Favatars%2Fava_0006-192.png",
                "image_512": "https:\/\/secure.gravatar.com\/avatar\/6fdedec551753aee3ca80c295794a088.jpg?s=512&d=https%3A%2F%2Fa.slack-edge.com%2F7fa9%2Fimg%2Favatars%2Fava_0006-512.png"
            },
            "is_admin": false,
            "is_owner": false,
            "is_primary_owner": false,
            "is_restricted": false,
            "is_ultra_restricted": false,
            "is_bot": false,
            "has_2fa": false,
            "presence": "active"
        }
