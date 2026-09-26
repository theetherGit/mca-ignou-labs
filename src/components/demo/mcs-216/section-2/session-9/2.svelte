<script>
    import { onMount } from "svelte";
    let content = $state("Loading external.html...");
    let error = $state("");

    onMount(() => {
        const xhr = new XMLHttpRequest();
        xhr.open(
            "GET",
            "/preview/mcs-216/section-2/session-9/external.html",
            true,
        );

        xhr.onload = function () {
            if (xhr.status === 200) content = xhr.responseText;
            else error = `Failed to load (Status: ${xhr.status})`;
        };
        xhr.onerror = () => {
            error = "Network/CORS error. Run on a local server.";
        };
        xhr.send();
    });
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl flex flex-col items-center justify-center gap-6"
>
    <h2 class="text-xl font-semibold text-gray-800">
        External Content Loader (onMount)
    </h2>

    {#if error}
        <p
            class="text-red-600 bg-red-50 px-4 py-2 rounded-lg border border-red-200"
        >
            {error}
        </p>
    {/if}

    <div
        class="w-full max-w-2xl border-2 border-dashed border-gray-300 p-6 bg-white rounded-xl shadow-sm min-h-25"
    >
        {@html content}
    </div>
</div>
