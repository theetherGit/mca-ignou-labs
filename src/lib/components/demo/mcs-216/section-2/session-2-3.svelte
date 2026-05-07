<script lang="ts">
    const initialState = {
        position: "",
        name: "",
        nationality: "",
        dob: "",
        address: "",
        phone: "",
        email: "",
        education: "",
        employmentHistory: "",
        yearsExp: 0,
        personalStatement: "",
        ref1: {
            name: "",
            occupation: "",
            relationship: "",
            address: "",
            phone: "",
        },
        ref2: {
            name: "",
            occupation: "",
            relationship: "",
            address: "",
            phone: "",
        },
    };

    let formData = $state({ ...initialState });
    let formEl: HTMLFormElement | undefined;
    let status = $state({ submitting: false, message: "", type: "" });

    function handleSubmit(e: Event) {
        e.preventDefault();
        if (!formEl?.checkValidity()) {
            formEl?.reportValidity();
            return;
        }

        status.submitting = true;
        status.message = "";
        status.type = "";

        // Simulate async submission
        setTimeout(() => {
            status.submitting = false;
            status.message =
                "✅ Application submitted successfully! We will review your details and contact you shortly.";
            status.type = "success";

            // Reset form state
            formData = { ...initialState };
        }, 1500);
    }

    const inputBase =
        "w-full px-3 py-2.5 border text-black border-gray-300 rounded-lg focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition bg-white";
    const labelBase = "block text-sm font-medium text-gray-700 mb-1.5";
    const reqMark = "text-red-500 ml-0.5";
</script>

<div
    class="min-h-svh mt-5 rounded-md bg-gray-50 py-8 px-4 sm:px-6 lg:px-8 flex items-center justify-center font-sans"
>
    <div
        class="w-full max-w-3xl bg-white rounded-2xl shadow-xl overflow-hidden"
    >
        <header class="bg-blue-600 px-6 py-5 text-center">
            <h1 class="text-2xl font-bold text-white">Ethercorps</h1>
            <p class="text-blue-100 mt-1 text-sm">
                Online Job Application Portal
            </p>
        </header>

        <form
            bind:this={formEl}
            onsubmit={handleSubmit}
            class="p-6 sm:p-8 space-y-6"
            novalidate
        >
            <!-- Personal & Contact -->
            <fieldset
                class="border border-gray-200 rounded-xl p-5 bg-gray-50/40"
            >
                <legend
                    class="text-base font-semibold text-blue-600 px-2 mb-4 -mt-3 bg-gray-50 w-fit"
                    >Personal & Contact Information</legend
                >
                <div class="grid grid-cols-1 md:grid-cols-2 gap-4">
                    <div class="md:col-span-2">
                        <label for="position" class={labelBase}
                            >Position Applied For <span class={reqMark}>*</span
                            ></label
                        >
                        <input
                            bind:value={formData.position}
                            type="text"
                            required
                            class={inputBase}
                            placeholder="e.g. Senior Frontend Developer"
                        />
                    </div>
                    <div>
                        <label class={labelBase} for="fullName"
                            >Full Name <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.name}
                            type="text"
                            required
                            class={inputBase}
                        />
                    </div>
                    <div>
                        <label class={labelBase} for="nationality"
                            >Nationality <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.nationality}
                            type="text"
                            required
                            class={inputBase}
                        />
                    </div>
                    <div>
                        <label class={labelBase} for="dob"
                            >Date of Birth <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.dob}
                            type="date"
                            required
                            class={inputBase}
                        />
                    </div>
                    <div>
                        <label class={labelBase} for="email"
                            >Email Address <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.email}
                            type="email"
                            required
                            class={inputBase}
                            placeholder="you@company.com"
                        />
                    </div>
                    <div class="md:col-span-2">
                        <label for="address" class={labelBase}>Address</label>
                        <textarea
                            bind:value={formData.address}
                            rows="2"
                            required
                            class={`${inputBase} resize-y min-h-20`}
                        ></textarea>
                    </div>
                    <div class="md:col-span-2">
                        <label class={labelBase} for="phone"
                            >Telephone Number <span class={reqMark}>*</span
                            ></label
                        >
                        <input
                            bind:value={formData.phone}
                            type="tel"
                            required
                            class={inputBase}
                            placeholder="+1 (555) 000-0000"
                        />
                    </div>
                </div>
            </fieldset>

            <!-- Education -->
            <fieldset
                class="border border-gray-200 rounded-xl p-5 bg-gray-50/40"
            >
                <legend
                    class="text-base font-semibold text-blue-600 px-2 mb-4 -mt-3 bg-gray-50 w-fit"
                    >Education & Qualifications</legend
                >
                <div>
                    <label class={labelBase} for="education"
                        >Educational History & Qualifications</label
                    >
                    <textarea
                        bind:value={formData.education}
                        rows="3"
                        class={`${inputBase} resize-y min-h-25`}
                        placeholder="Degrees, certifications, institutions, graduation dates..."
                    ></textarea>
                </div>
            </fieldset>

            <!-- Work Experience -->
            <fieldset
                class="border border-gray-200 rounded-xl p-5 bg-gray-50/40"
            >
                <legend
                    class="text-base font-semibold text-blue-600 px-2 mb-4 -mt-3 bg-gray-50 w-fit"
                    >Work Experience & Training</legend
                >
                <div class="space-y-4">
                    <div>
                        <label class={labelBase} for="employer"
                            >Employer History & Training</label
                        >
                        <textarea
                            bind:value={formData.employmentHistory}
                            rows="3"
                            class={`${inputBase} resize-y min-h-25`}
                            placeholder="Previous companies, roles, key responsibilities, training programs..."
                        ></textarea>
                    </div>
                    <div>
                        <label for="yoe" class={labelBase}
                            >Years of Experience</label
                        >
                        <div class="flex items-center gap-4 mt-1">
                            <input
                                bind:value={formData.yearsExp}
                                type="range"
                                min="0"
                                max="10"
                                step="1"
                                class="w-full h-2 bg-gray-200 rounded-lg appearance-none cursor-pointer accent-blue-600"
                            />
                            <span
                                class="min-w-[3ch] text-center font-semibold text-blue-700 bg-blue-50 px-2 py-1 rounded-md border border-blue-200"
                                >{formData.yearsExp} yrs</span
                            >
                        </div>
                    </div>
                </div>
            </fieldset>

            <!-- Personal Statement -->
            <fieldset
                class="border border-gray-200 rounded-xl p-5 bg-gray-50/40"
            >
                <legend
                    class="text-base font-semibold text-blue-600 px-2 mb-4 -mt-3 bg-gray-50 w-fit"
                    >Personal Statement</legend
                >
                <div>
                    <label for="self-reason" class={labelBase}
                        >Why are you a strong candidate? <span class={reqMark}
                            >*</span
                        ></label
                    >
                    <textarea
                        bind:value={formData.personalStatement}
                        rows="4"
                        required
                        class={`${inputBase} resize-y min-h-30`}
                        placeholder="Highlight your skills, motivation, and career objectives..."
                    ></textarea>
                </div>
            </fieldset>

            <!-- Referees -->
            <fieldset
                class="border border-gray-200 rounded-xl p-5 bg-gray-50/40"
            >
                <legend
                    class="text-base font-semibold text-blue-600 px-2 mb-4 -mt-3 bg-gray-50 w-fit"
                    >Referees</legend
                >
                <div class="grid grid-cols-1 md:grid-cols-2 gap-6">
                    <!-- Referee 1 -->
                    <div
                        class="space-y-3 bg-white p-4 rounded-lg border border-gray-200 shadow-sm"
                    >
                        <h3 class="font-medium text-gray-800 border-b pb-2">
                            Referee 1
                        </h3>
                        <label class={labelBase} for="referee_1_fname"
                            >Full Name <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref1.name}
                            type="text"
                            required
                            class={inputBase}
                        />
                        <label class={labelBase} for="referee_1_occupation"
                            >Occupation <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref1.occupation}
                            type="text"
                            required
                            class={inputBase}
                        />
                        <label class={labelBase} for="referee_1_relation"
                            >Relationship <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref1.relationship}
                            type="text"
                            required
                            class={inputBase}
                            placeholder="e.g. Former Manager"
                        />
                        <label class={labelBase} for="referee_1_address"
                            >Address <span class={reqMark}>*</span></label
                        >
                        <textarea
                            bind:value={formData.ref1.address}
                            rows="2"
                            required
                            class={`${inputBase} resize-y min-h-17.5`}
                        ></textarea>
                        <label class={labelBase} for="referee_1_phone"
                            >Telephone <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref1.phone}
                            type="tel"
                            required
                            class={inputBase}
                        />
                    </div>

                    <!-- Referee 2 -->
                    <div
                        class="space-y-3 bg-white p-4 rounded-lg border border-gray-200 shadow-sm"
                    >
                        <h3 class="font-medium text-gray-800 border-b pb-2">
                            Referee 2
                        </h3>
                        <label class={labelBase} for="referee_2_name"
                            >Full Name <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref2.name}
                            type="text"
                            required
                            class={inputBase}
                        />
                        <label class={labelBase} for="referee_2_occupation"
                            >Occupation <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref2.occupation}
                            type="text"
                            required
                            class={inputBase}
                        />
                        <label class={labelBase} for="referee_2_relation"
                            >Relationship <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref2.relationship}
                            type="text"
                            required
                            class={inputBase}
                        />
                        <label class={labelBase} for="referee_2_address"
                            >Address <span class={reqMark}>*</span></label
                        >
                        <textarea
                            bind:value={formData.ref2.address}
                            rows="2"
                            required
                            class={`${inputBase} resize-y min-h-17.5`}
                        ></textarea>
                        <label class={labelBase} for="referee_2_phone"
                            >Telephone <span class={reqMark}>*</span></label
                        >
                        <input
                            bind:value={formData.ref2.phone}
                            type="tel"
                            required
                            class={inputBase}
                        />
                    </div>
                </div>
            </fieldset>

            <!-- Submit & Message -->
            <div class="flex flex-col items-center gap-3 pt-2">
                <button
                    type="submit"
                    disabled={status.submitting}
                    class="bg-blue-600 hover:bg-blue-700 text-white font-semibold py-2.5 px-8 rounded-lg transition shadow-md disabled:opacity-60 disabled:cursor-not-allowed w-full sm:w-auto"
                >
                    {status.submitting ? "Submitting..." : "Submit Application"}
                </button>
                {#if status.message}
                    <p
                        class={`w-full text-center text-sm font-medium py-2 px-3 rounded-lg transition ${status.type === "success" ? "bg-green-50 text-green-700 border border-green-200" : "bg-red-50 text-red-700 border border-red-200"}`}
                    >
                        {status.message}
                    </p>
                {/if}
            </div>
        </form>
    </div>
</div>
