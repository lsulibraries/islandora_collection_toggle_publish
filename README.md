## Islandora Collection Toggle Publish

Islandora module providing a publish/unpublish toggle for collections.

### Permissions

- `Administer unpublished collection setting.`: Roles with this permission can toggle publish for collections. They can also view collections that have been unpublished.
- `administer publish toggle defaults`: Roles with this permission can alter site-level settings at `/admin/islandora/tools/collection_toggle_publish`.

### Settings

- `Published by default`: Whether new collections are published or unpublished at ingest.
- `multisite locations`: (for use in a multisite deployment) Comma-separated list of other sites to update when a collection is set published/unpublished.

