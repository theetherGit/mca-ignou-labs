<script lang="ts">
    import { siteConfig } from "$lib/site-config";
    import "../app.css";
    import { useSiteConfig } from "@ethercorps/kit";

    let { children } = $props();

    useSiteConfig(() => siteConfig);
</script>

{@render children?.()}
