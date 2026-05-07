<script lang="ts">
    import { browser } from "$app/environment";
    import { onMount } from "svelte";
    let statusMsg = $state("Initializing...");
    let questionContainer: HTMLDivElement | undefined = $state();
    let doneOnce = $state(false);

    onMount(() => {
        const observer = new IntersectionObserver(
            (entries) => {
                entries.forEach((entry) => {
                    if (entry.isIntersecting && !doneOnce) {
                        if (navigator.cookieEnabled) {
                            statusMsg = "Cookies are enabled";
                        } else {
                            statusMsg = "Cookies are disabled";
                        }
                        doneOnce = true;
                        setTimeout(() => alert(statusMsg), 1000);
                    }
                });
            },
            {
                threshold: 0.1,
            },
        );

        if (questionContainer) {
            observer.observe(questionContainer);
        }
    });
</script>

<div
    bind:this={questionContainer}
    class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl flex items-center justify-center"
>
    <div class="bg-white p-6 rounded-xl shadow-lg text-center max-w-md w-full">
        <h2 class="text-xl font-semibold mb-4 text-gray-800">
            Exercise 2: Cookie Status
        </h2>
        <p
            class="text-lg font-medium px-4 py-2 rounded bg-blue-50 text-blue-700"
        >
            {statusMsg}
        </p>
        <p class="text-sm text-gray-500 mt-3">
            Alert shown when scrolled to this section, Only once.
        </p>
    </div>
</div>
